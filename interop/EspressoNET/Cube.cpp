#include "Cube.h"

#include <atomic>

using System::ArgumentException;
using System::OutOfMemoryException;
using System::Collections::Generic::Dictionary;
using System::Threading::Monitor;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{
    std::atomic<unsigned int> id_counter(0);
    static unsigned int id_of_active_cube = 0;

    Dictionary<unsigned int, Cube> cubes = gcnew Dictionary<unsigned int, Cube>();

    /// <summary>
    /// Initializes the global variables that store cube data.
    /// After this function the system appears to be in the initial state.
    /// </summary>
    void initialize_global_cube()
    {
        cube.size = 0;
        cube.num_vars = 0;
        cube.num_binary_vars = 0;
        cube.first_part = nullptr;
        cube.last_part = nullptr;
        cube.part_size = nullptr;
        cube.first_word = nullptr;
        cube.last_word = nullptr;
        cube.binary_mask = nullptr;
        cube.mv_mask = nullptr;
        cube.var_mask = nullptr;
        cube.temp = nullptr;
        cube.fullset = nullptr;
        cube.emptyset = nullptr;
        cube.inmask = 0;
        cube.inword = 0;
        cube.sparse = nullptr;
        cube.num_mv_vars = 0;
        cube.output = 0;

        cdata.part_zeros = nullptr;
        cdata.var_zeros = nullptr;
        cdata.parts_active = nullptr;
        cdata.is_unate = nullptr;
        cdata.vars_active = 0;
        cdata.vars_unate = 0;
        cdata.best = 0;
    }

    void Cube::save_previous_cube()
    {
        if (id_of_active_cube != 0)
        {
            // Copy the global variables to the previous cube,
            // in case they have been updated
            auto current = cubes[id_of_active_cube];
            *current.cube_ = cube;
            *current.cdata_ = cdata;
        }
    }

    void Cube::update_current_cube()
    {
        *cube_ = cube;
        *cdata_ = cdata;
    }

    void Cube::copy_cube()
    {
        cube = *cube_;
        cdata = *cdata_;
    }

    Cube::Cube(const unsigned int number_of_input_variables, const unsigned int number_of_output_variables)
    : disposed_(false)
    , id_(++id_counter)
    , number_of_input_variables_(number_of_input_variables)
    , number_of_output_variables_(number_of_output_variables)
    {
        if (number_of_input_variables == 0)
        {
            throw gcnew ArgumentException("Number of input variables must be greater than zero", "number_of_input_variables");
        }
        if (number_of_output_variables == 0)
        {
            throw gcnew ArgumentException("Number of output variables must be greater than zero", "number_of_output_variables");
        }

        cube_ = static_cast<cube_struct*>(malloc(sizeof(cube_struct)));
        if (cube_ == nullptr)
        {
            throw gcnew OutOfMemoryException("Failed to allocate memory for cube");
        }

        cdata_ = static_cast<cdata_struct*>(malloc(sizeof(cdata_struct)));
        if (cdata_ == nullptr)
        {
            free(cube_);
            throw gcnew OutOfMemoryException("Failed to allocate memory for cdata");
        }

        enter();
        try
        {
            save_previous_cube();
            initialize_global_cube();

            pla_ = new_PLA();
            pla_->pla_type = FD_type;

            // The following code is taken from the Espresso source code
            // (file: cvrin.c, method: parse_pla)
            cube.num_binary_vars = number_of_input_variables;
            cube.num_vars = cube.num_binary_vars + 1;
            cube.part_size = ALLOC(int, cube.num_vars);

            cube.part_size[cube.num_vars - 1] = number_of_output_variables;
            cube_setup();
            PLA_labels(pla_);

            update_current_cube();

            cubes[id_] = *this;
            id_of_active_cube = id_;
        }
        finally
        {
            exit();
        }
    }

    Cube::!Cube()
    {
        enter();
        try
        {
            if (id_of_active_cube != id_)
            {
                save_previous_cube();
                copy_cube();
            }

            // Free memory used by the cube
            setdown_cube();

            initialize_global_cube();
            id_of_active_cube = 0;
        }
        finally
        {
            exit();
        }

        free(cube_);
        free(cdata_);

        cube_ = nullptr;
        cdata_ = nullptr;
    }

    void Cube::enter()
    {
        Monitor::Enter(lock_);
    }

    void Cube::exit()
    {
        Monitor::Exit(lock_);
    }

}
