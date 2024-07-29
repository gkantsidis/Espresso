#pragma once

#ifndef SET_FAMILY
#define SET_FAMILY

#include "externals.h"
#include "Set.h"

using System::Boolean;
using System::Text::StringBuilder;
using System::Threading::Monitor;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
    /// <summary>
    /// TODO: Add class summary
    /// <</summary>
    // ReSharper disable once CppInconsistentNaming
    public ref class SetFamilyGarbage sealed
    {
    public:
        static void cleanup();

        static void enter()
        {
            Monitor::Enter(lock_);
        }

        static void exit()
        {
            Monitor::Exit(lock_);
        }

    private:
        // ReSharper disable once CppUseAuto
        static Object^ lock_ = gcnew Object();
    };

    /// <summary>
    /// TODO: Add class summary
    /// </summary>
    // ReSharper disable once CppInconsistentNaming
    public ref class SetFamily sealed
    {
    public:
        SetFamily(const int number_of_sets, const int number_of_set_elements);
        SetFamily(const SetFamily^ set);
        //SetFamily(const SetFamily% rhs) {}

        ~SetFamily()
        {
            if (disposed_)
            {
                return;
            }
            this->!SetFamily();
            disposed_ = true;
        }

        !SetFamily();

        SetFamily^ clone()
        {
            return gcnew SetFamily(this);
        }

        SetFamily^ make_all_active()
        {
            sf_active(set_);
            return this;
        }

        SetFamily^ add(Set^ set);
        SetFamily^ del(int i);

        // ReSharper disable once CppInconsistentNaming
        static SetFamily^ Espresso(SetFamily^ f, SetFamily^ d1, SetFamily^ r);

        void append(StringBuilder^ sb);

        String^ ToString() override;

        /* The following expose the internal members of the
         * native structure. This is used to understand and
         * debug the interface
         */

        property int InternalSizeInIntegers
        {
	        int get()
	        {
                return this->set_->wsize;
	        }
        }

        property int InternalUserDeclaredSetSize
        {
	        int get()
	        {
                return this->set_->sf_size;
	        }
        }

        property int InternalCapacity
        {
	        int get()
	        {
                return this->set_->capacity;
	        }
        }

        property int InternalCount
        {
	        int get()
	        {
                return this->set_->count;
	        }
        }

        property int InternalActiveCount
        {
	        int get()
	        {
                return this->set_->active_count;
	        }
        }

    internal:
        SetFamily(const pset_family set);

    private:
        pset_family set_;
        Boolean disposed_;
    };

}

#endif
