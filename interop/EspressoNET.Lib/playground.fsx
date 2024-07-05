#r @"..\..\x64\Debug\EspressoNET.dll"

open Espresso

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


let sf = new SetFamily(4, 8)
sf.make_all_active()
sf.ToString()
