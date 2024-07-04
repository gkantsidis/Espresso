#pragma once

#include "externals.h"

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
	

// ReSharper disable once CppInconsistentNaming
public ref class SetFamily sealed
{
public:
	static void cleanup()
	{
		sf_cleanup();
	}

	SetFamily(const int number_of_sets, const int number_of_set_elements);

	~SetFamily()
	{
		if (disposed_)
		{
			return;
		}
		this->!SetFamily();

		disposed_ = true;
	}

	!SetFamily()
	{
		if (set_ != nullptr)
		{
			sf_free(set_);
		}
		set_ = nullptr;
	}

private:
	pset_family set_;
	bool disposed_;
};

}
