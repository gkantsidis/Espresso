// ReSharper disable CppInconsistentNaming
#pragma once

#include "externals.h"

using System::Boolean;

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{

	// ReSharper disable once CppInconsistentNaming
	public ref class Runtime sealed
	{
	public:
		static property int DebugLevel
		{
			int get()
			{
				return debug;
			}
			void set(const int value)
			{
				debug = value;
			}
		}

		static property Boolean VerboseDebug
		{
			Boolean get()
			{
				return verbose_debug ? true : false;
			}
			void set(const Boolean value)
			{
				verbose_debug = value;
			}
		}

		static property Boolean EchoComments
		{
			Boolean get()
			{
				return echo_comments ? true : false;
			}
			void set(const Boolean value)
			{
				echo_comments = value;
			}
		}

		static property Boolean EchoUnknownCommands
		{
			Boolean get()
			{
				return echo_unknown_commands ? true : false;
			}
			void set(const Boolean value)
			{
				echo_unknown_commands = value;
			}
		}

		static property Boolean ForceIrredundant
		{
			Boolean get()
			{
				return force_irredundant ? true : false;
			}
			void set(const Boolean value)
			{
				force_irredundant = value;
			}
		}

		static property Boolean SkipMakeSparse
		{
			Boolean get()
			{
				return skip_make_sparse ? true : false;
			}
			void set(const Boolean value)
			{
				skip_make_sparse = value;
			}
		}

		static property Boolean KissOption
		{
			Boolean get()
			{
				return kiss ? true : false;
			}
			void set(const Boolean value)
			{
				kiss = value;
			}
		}

		static property Boolean PosOption
		{
			Boolean get()
			{
				return pos ? true : false;
			}
			void set(const Boolean value)
			{
				pos = value;
			}
		}

		static property Boolean PrintSolution
		{
			Boolean get()
			{
				return print_solution ? true : false;
			}
			void set(const Boolean value)
			{
				print_solution = value;
			}
		}

		static property Boolean RecomputeOnSet
		{
			Boolean get()
			{
				return recompute_onset ? true : false;
			}
			void set(const Boolean value)
			{
				recompute_onset = value;
			}
		}

		static property Boolean RemoveEssential
		{
			Boolean get()
			{
				return remove_essential ? true : false;
			}
			void set(const Boolean value)
			{
				remove_essential = value;
			}
		}

		static property Boolean SingleExpand
		{
			Boolean get()
			{
				return single_expand ? true : false;
			}
			void set(const Boolean value)
			{
				single_expand = value;
			}
		}

		static property Boolean PrintSummary
		{
			Boolean get()
			{
				return summary ? true : false;
			}
			void set(const Boolean value)
			{
				summary = value;
			}
		}

		static property Boolean Trace
		{
			Boolean get()
			{
				return trace ? true : false;
			}
			void set(const Boolean value)
			{
				trace = value;
			}
		}

		static property Boolean UnwrapOnSet
		{
			Boolean get()
			{
				return unwrap_onset ? true : false;
			}
			void set(const Boolean value)
			{
				unwrap_onset = value;
			}
		}

		static property Boolean RandomOrder
		{
			Boolean get()
			{
				return use_random_order ? true : false;
			}
			void set(const Boolean value)
			{
				use_random_order = value;
			}
		}

		static void FullDebug()
		{
			EchoComments = true;
			EchoUnknownCommands = true;
			PrintSolution = true;
			PrintSummary = true;
			Trace = true;
			// TODO: What are the debug levels?
			DebugLevel = 5;
		}
	};

}
