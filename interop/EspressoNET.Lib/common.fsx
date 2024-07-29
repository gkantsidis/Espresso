#r @"..\..\x64\Debug\EspressoNET.dll"

open System.IO

[<AutoOpen>]
module EspressoFsiHelpers =
    let private SAMPLES = Path.Combine(__SOURCE_DIRECTORY__, "samples")
    let private EXAMPLES = Path.Combine(__SOURCE_DIRECTORY__, "..", "..", "examples")

    let get_sample filename = Path.Combine(SAMPLES, filename)
    let get_list_of_examples () = Directory.EnumerateFiles(EXAMPLES)
    let get_example filename = Path.Combine(EXAMPLES, filename)
