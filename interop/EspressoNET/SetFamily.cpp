#include "SetFamily.h"

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
	
SetFamily::SetFamily(const int number_of_sets, const int number_of_set_elements)
{
    if (number_of_sets <= 0)
    {
        throw gcnew System::ArgumentOutOfRangeException("number_of_sets", number_of_sets, "Number of sets must be positive");
    }
    if (number_of_set_elements <= 0)
    {
        throw gcnew System::ArgumentOutOfRangeException("number_of_set_elements", number_of_set_elements, "Number of set elements must be positive");
    }

    this->set_ = sf_new(number_of_sets, number_of_set_elements);
    // If the allocation had failed, the native library would have failed
    assert(this->set_ != nullptr);
}

}
