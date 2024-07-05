#pragma once

#include "externals.h"

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{

// ReSharper disable once CppInconsistentNaming
public ref class Set sealed
{
public:
    Set(const int size)
    {
        if (size <= 0)
        {
            throw gcnew System::ArgumentOutOfRangeException("size", size, "Size must be positive");
        }

        this->set_ = set_new(size);
        // If the allocation had failed, the native library would have failed
        assert(this->set_ != nullptr);

        this->size_ = size;
        this->disposed_ = false;
    }

    ~Set()
    {
        if (disposed_)
        {
            return;
        }

        this->!Set();
        disposed_ = true;
    }

    !Set()
    {
        if (set_ != nullptr)
        {
            set_free(set_);
            set_ = nullptr;
        }
    }

    static Set^ mk_full(const int size)
    {
        if (size <= 0)
        {
            throw gcnew System::ArgumentOutOfRangeException("size", size, "Size must be positive");
        }

        return gcnew Set(set_full(size));
    }

    static Set^ mk_empty(const int size)
    {
        return gcnew Set(size);
    }

    Set^ clone()
    {
        return gcnew Set(set_save(set_), size_);
    }

    bool is_in_set(const int element)
    {
        if (element < 0 || set_ == nullptr)
        {
            return false;
        }
        return is_in_set(set_, element);
    }

    bool add(const int element)
    {
        if (element < 0 || set_ == nullptr)
        {
            return false;
        }
        return set_insert(set_, element);
    }

    bool remove(const int element)
    {
        if (element < 0 || set_ == nullptr)
        {
            return false;
        }
        return set_remove(set_, element);
    }

private:
    pset set_;
    int size_;
    bool disposed_;

    Set(const pset set, const int size)
    {
        this->set_ = set;
        this->size_ = size;
        this->disposed_ = false;
    }

    bool is_valid(const int element)
    {
        return element >= 0 && set_ != nullptr;
    }
};

}
