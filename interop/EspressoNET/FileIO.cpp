#include "externals.h"
#include "PLA.h"

using System::String;
using System::Boolean;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{

	// ReSharper disable once CppInconsistentNaming
	public ref class Readers sealed
	{
	public:
		static PLA^ read_pla_from_file(String^ filename, const int needs_do_not_care_set, const int needs_offset, PLAType type)
		{
			return PLA::read_pla_from_file(filename, needs_do_not_care_set, needs_offset, type);
		}
		static PLA^ read_pla_from_file(String^ filename, const Boolean needs_do_not_care_set, const Boolean needs_offset, PLAType type)
		{
			const int do_not_care_set = needs_do_not_care_set;
			const int offset = needs_offset;
			return read_pla_from_file(filename, do_not_care_set, offset, type);
		}
	};

}