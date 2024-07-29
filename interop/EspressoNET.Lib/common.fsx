#r @"..\..\x64\Debug\EspressoNET.dll"

open System.IO

[<AutoOpen>]
module EspressoFsiHelpers =
    let SAMPLES = Path.Combine(__SOURCE_DIRECTORY__, "samples")

    let get_sample filename = Path.Combine(SAMPLES, filename)
