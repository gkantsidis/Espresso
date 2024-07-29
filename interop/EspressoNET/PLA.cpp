#include "PLA.h"

#include "signature.h"

using System::String;
using System::IntPtr;
using System::IO::File;
using System::IO::FileStream;
using System::IO::FileMode;
using System::Runtime::InteropServices::Marshal;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
	PLA::PLA()
	{
		this->pla_ = new_PLA();
		this->disposed_ = false;
	}

	PLA::!PLA()
	{
		if (this->pla_ != nullptr)
		{
			free_PLA(this->pla_);
		}
		this->pla_ = nullptr;
	}

	PLA^ PLA::read_pla_from_file(String^ filename, const int needs_do_not_care_set, const int needs_offset, PLAType type)
	{
		if (String::IsNullOrWhiteSpace(filename))
		{
			throw gcnew System::ArgumentNullException("filename", "Filename should not be null or empty");
		}
		if (File::Exists(filename) == false)
		{
			throw gcnew System::IO::FileNotFoundException("File does not exist", filename);
		}

		const auto pla_type = type.Data;

		FILE* fp = nullptr;
		try
		{
			auto p = Marshal::StringToHGlobalAnsi(filename);
			const auto filename_pointer = static_cast<char*>(p.ToPointer());
			const auto status_file_open = fopen_s(&fp, filename_pointer, "rt");
			Marshal::FreeHGlobal(p);
			if (status_file_open != 0)
			{
				auto error_message = String::Format("Error opening input file {0}, error code: {1}",
					filename, status_file_open);
				throw gcnew System::IO::FileLoadException(error_message, filename);
			}

			pPLA pla = nullptr;
			const int status = read_pla(fp, needs_do_not_care_set, needs_offset, pla_type, &pla);
			if (status < 0)
			{
				auto error_message = String::Format("Error parsing from file {0}, error code: {1}",
					filename, status);
				throw gcnew System::IO::FileLoadException(error_message, filename);
			}

			return gcnew PLA(pla);
		}
		finally
		{
			if (fp != nullptr)
			{
				fclose(fp);
			}
		}
	}

	PLA^ PLA::read_pla_from_file(String^ filename, const Boolean needs_do_not_care_set, const Boolean needs_offset, PLAType type)
	{
		const int do_not_care_set = needs_do_not_care_set;
		const int offset = needs_offset;

		return read_pla_from_file(filename, do_not_care_set, offset, type);
	}

	SetFamily^ PLA::on_set()
	{
		return gcnew SetFamily(sf_save(this->pla_->F));
	}

	SetFamily^ PLA::off_set()
	{
		return gcnew SetFamily(sf_save(this->pla_->D));
	}

	SetFamily^ PLA::do_not_care_set()
	{
		return gcnew SetFamily(sf_save(this->pla_->R));
	}

	SetFamily^ PLA::run_espresso()
	{
		const auto result = espresso(sf_save(this->pla_->F), this->pla_->D, this->pla_->R);
		return gcnew SetFamily(result);
	}

	SetFamily^ PLA::run_canonical_cover()
	{
		const auto result = find_canonical_cover(this->pla_->F, this->pla_->D, this->pla_->R);
		return gcnew SetFamily(result);
	}

	SetFamily^ PLA::run_minimize_exact(const Boolean use_exact_cover)
	{
		const int exact_cover = use_exact_cover;
		const auto result = minimize_exact(this->pla_->F, this->pla_->D, this->pla_->R, exact_cover);
		return gcnew SetFamily(result);
	}

	SetFamily^ PLA::run_minimize_exact_literals(const Boolean use_exact_cover)
	{
		const int exact_cover = use_exact_cover;
		const auto result = minimize_exact_literals(this->pla_->F, this->pla_->D, this->pla_->R, exact_cover);
		return gcnew SetFamily(result);
	}

	PLA::PLA(const pPLA pla)
	{
		if (pla != nullptr)
		{
			this->pla_ = pla;
			this->disposed_ = false;
		}
		else
		{
			// TODO: give a warning here
			this->pla_ = nullptr;
			this->disposed_ = true;
		}
		
	}

}
