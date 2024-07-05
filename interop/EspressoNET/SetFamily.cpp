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
        this->disposed_ = false;
    }
    finally
    {
        SetFamilyGarbage::exit();
    }
}

Espresso::SetFamily::SetFamily(const pset_family set)
{
    if (set == nullptr)
    {
	    throw gcnew System::ArgumentNullException("set", "Set must not be null");
    }

    this->set_ = set;
    this->disposed_ = false;
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

SetFamily^ SetFamily::add(Set^ set)
{
    sf_addset(this->set_, set->get_set());
    return this;
}

SetFamily^ SetFamily::del(int i)
{
    sf_delset(this->set_, i);
    return this;
}

SetFamily^ SetFamily::espresso(SetFamily^ f, SetFamily^ d1, SetFamily^ r)
{
    // TODO: Figure out whether we need to lock for this call.
    auto cover = espresso(f, d1, r);
    return gcnew SetFamily(cover);
}

void SetFamily::append(StringBuilder^ sb)
{
    pset p = this->set_->data;
    const auto increment = this->set_->wsize;
    const auto sf_size = this->set_->sf_size;

    for(int i=0; i < this->set_->count; p += increment, i++)
    {
        sb->AppendFormat("[{0:4}] ", i);

        for (int j=0; j < sf_size; j++)
        {
            sb->Append(is_in_set(p, j) ? "1" : "0");
        }
        sb->AppendLine();
    }
}

System::String^ SetFamily::ToString()
{
    auto sb = gcnew StringBuilder();
    this->append(sb);
    auto str = sb->ToString();

    // TODO: Consider to return a subset of the string str, if it is unreasonable large
    return str;
}

}
