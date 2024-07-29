#pragma once

#ifndef EXTERNALS
#define EXTERNALS

//#pragma push_macro("_ALLOW_KEYWORD_MACROS")
//#define _ALLOW_KEYWORD_MACROS
extern "C" {
	#include "espresso.h"

	extern pcover espresso(pset_family F, pset_family D1, pset_family R);
	extern pcover find_canonical_cover(pset_family F, pset_family D1, pset_family R);
}
//#pragma pop_macro("_ALLOW_KEYWORD_MACROS")

#endif
