#pragma once

#include "externals.h"

// ReSharper disable once CppInconsistentNaming
namespace Espresso
{

	// ReSharper disable once CppInconsistentNaming
	public ref class Runtime sealed
	{
	public:
		static void enable_tracing()
		{
			trace = 1;
		}

		static void disable_tracing()
		{
			trace = 0;
		}

		static void enable_summary()
		{
			summary = 1;
		}

		static void disable_summary()
		{
			summary = 0;
		}

		static void enable_random_order()
		{
			use_random_order = 1;
		}

		static void disable_random_order()
		{
			use_random_order = 0;
		}

		static void enable_verbose_debug()
		{
			verbose_debug = 1;
		}

		static void disable_verbose_debug()
		{
			verbose_debug = 0;
		}

		static void set_debug_level(const int level)
		{
			debug = level;
		}
	};

}