#pragma once

#include "externals.h"

using System::Boolean;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
    // ReSharper disable once CppInconsistentNaming
    public ref class Cube sealed
    {
    public:
        Cube(const unsigned int number_of_input_variables, const unsigned int number_of_output_variables);

        ~Cube()
        {
            if (disposed_)
            {
                return;
            }
            this->!Cube();
            disposed_ = true;
        }

        !Cube();

        property unsigned int Id
        {
            unsigned int get()
            {
                return id_;
            }
        }

        property unsigned int NumberOfInputVariables
        {
            unsigned int get()
            {
                return number_of_input_variables_;
            }
        }

        property unsigned int NumberOfOutputVariables
        {
            unsigned int get()
            {
                return number_of_output_variables_;
            }
        }

    private:
        Boolean disposed_;

        unsigned int id_;
        unsigned int number_of_input_variables_;
        unsigned int number_of_output_variables_;

        static Object^ lock_ = gcnew Object();
        static void enter();
        static void exit();
        static void save_previous_cube();
        void update_current_cube();
        void copy_cube();

        struct cube_struct * cube_;
        struct cdata_struct * cdata_;
        pPLA pla_;
    };

}

