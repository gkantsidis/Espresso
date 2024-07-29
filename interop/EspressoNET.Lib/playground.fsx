#load "common.fsx"

open Common
open Espresso


let example = get_example "tcheck"
let pla = Readers.read_pla_from_file(example, true, true, PLAType.fd)

let on_set = pla.on_set()
let off_set = pla.off_set()
let do_not_care_set = pla.do_not_care_set()
printf "On set:\n%A\n-------------\n" on_set
printf "Off set:\n%A\n-------------\n" off_set
printf "Do not care set\n%A\n-------------\n" do_not_care_set

