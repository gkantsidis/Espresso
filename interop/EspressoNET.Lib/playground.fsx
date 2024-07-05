#r @"..\..\x64\Debug\EspressoNET.dll"

open Espresso

let sf = new SetFamily(4, 8)
sf.make_all_active()
sf.ToString()
