#pragma once

#include <mutex>

#include "externals.h"
#include "Set.h"

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

    private:
        pset_family set_;
        bool disposed_;

        SetFamily(const pset_family set);
    };

}
