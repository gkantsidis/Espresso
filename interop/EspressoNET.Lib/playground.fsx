#r @"..\..\x64\Debug\EspressoNET.dll"

open Espresso

Runtime.enable_tracing()
Runtime.enable_verbose_debug()
Runtime.set_debug_level(5)

let myset = new Set(10)
myset.size()

myset.ToString()

myset.is_set(3)

myset.add(3)
myset.is_set(3)
myset.ToString()

myset.Dispose()

myset.add(5)
myset.is_set(5)
myset.ToString()

let myset2 = new Set(8);
let myset3 = new Set(8);

let sf = new SetFamily(4, 8)
sf.add(myset2).add(myset3)
sf.make_all_active()
printfn "\n%s\n" (sf.ToString())

let x1 = new SetFamily(4, 8)
let x2 = new SetFamily(4, 8)
// The following crashes
let oo = SetFamily.Espresso(sf, x1, x2)
