#include "SetFamily.h"

using System::Object;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{

    void SetFamilyGarbage::cleanup()
    {
        enter();
        try
        {
            sf_cleanup();
        }
        finally
        {
            exit();
        }
    }

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

    SetFamilyGarbage::enter();
    try
    {
        this->set_ = sf_new(number_of_sets, number_of_set_elements);
        // If the allocation had failed, the native library would have failed
        assert(this->set_ != nullptr);
    }
    finally
    {
        SetFamilyGarbage::exit();
    }

    this->disposed_ = false;
}

SetFamily::SetFamily(const SetFamily^ set)
{
    if (set == nullptr)
    {
        throw gcnew System::ArgumentNullException("set", "Set must not be null");
    }

    SetFamilyGarbage::enter();
    try
    {
        this->set_ = sf_save(set->set_);
    }
    finally
    {
        SetFamilyGarbage::exit();
    }
}

SetFamily::!SetFamily()
{
    if (set_ != nullptr)
    {
        SetFamilyGarbage::enter();
        try
        {
            sf_free(set_);
        }
        finally
        {
            SetFamilyGarbage::exit();
        }
    }
    set_ = nullptr;
}

}
