#pragma once

#include "externals.h"
#include "SetFamily.h"

using System::String;
using System::Boolean;
using System::Collections::Specialized::BitVector32;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
    // ReSharper disable once CppInconsistentNaming
    public ref class PLAType sealed
    {
    public:
        static const PLAType^ f = gcnew PLAType(F_type);
        static const PLAType^ d = gcnew PLAType(D_type);
        static const PLAType^ r = gcnew PLAType(R_type);
        static const PLAType^ pleasure = gcnew PLAType(PLEASURE_type);
        static const PLAType^ equations = gcnew PLAType(EQNTOTT_type);
        static const PLAType^ kiss = gcnew PLAType(KISS_type);
        static const PLAType^ constraints = gcnew PLAType(CONSTRAINTS_type);
        static const PLAType^ symbolic = gcnew PLAType(SYMBOLIC_CONSTRAINTS_type);
        static const PLAType^ fd = gcnew PLAType(FD_type);
        static const PLAType^ fr = gcnew PLAType(FR_type);
        static const PLAType^ dr = gcnew PLAType(DR_type);
        static const PLAType^ fdr = gcnew PLAType(FDR_type);

        PLAType(BitVector32^ mask)
        {
            this->mask_ = gcnew BitVector32(mask->Data);
        }
        PLAType(const int mask)
        {
            this->mask_ = gcnew BitVector32(mask);
        }
        PLAType(const PLAType% rhs)
        {
            this->mask_ = rhs.mask_;
        }

        String^ ToString() override
        {
            return this->mask_->ToString();
        }

    internal:
        property int Data
        {
            int get()
            {
                return this->mask_->Data;
            }
        }

    private:
        BitVector32^ mask_;
    };

    // ReSharper disable once CppInconsistentNaming
    public ref class PLA sealed
    {
    public:
        PLA();

        ~PLA()
        {
            if (disposed_)
            {
                return;
            }
            this->!PLA();
            disposed_ = true;
        }

        !PLA();

        static PLA^ read_pla_from_file(String^ filename, const int needs_do_not_care_set, const int needs_offset, PLAType type);
        static PLA^ read_pla_from_file(String^ filename, const Boolean needs_do_not_care_set, const Boolean needs_offset, PLAType type);

        void initialize_labels()
        {
            PLA_labels(this->pla_);
        }

        void summary()
        {
            PLA_summary(this->pla_);
        }

        SetFamily^ on_set();
        SetFamily^ off_set();
        SetFamily^ do_not_care_set();

        SetFamily^ run_espresso();
        SetFamily^ run_canonical_cover();
        SetFamily^ run_minimize_exact(const Boolean use_exact_cover);
        SetFamily^ run_minimize_exact_literals(const Boolean use_exact_cover);

    private:
        pPLA pla_;
        Boolean disposed_;

        PLA(const pPLA pla);
    };


}

