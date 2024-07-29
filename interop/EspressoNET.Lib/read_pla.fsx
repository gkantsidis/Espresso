#load "common.fsx"

open Common
open Espresso

let sample_file_1 = get_sample "temp.in"
let pla = Readers.read_pla_from_file(sample_file_1, true, true, PLAType.fd)
pla.summary()

let on_set = pla.on_set()
let off_set = pla.off_set()
let do_not_care_set = pla.do_not_care_set()
printf "\n%A\n" on_set
printf "\n%A\n" off_set
printf "\n%A\n" do_not_care_set

let result = pla.run_espresso()
pla.summary()
printf "\n%A\n" result

let canonical_cover = pla.run_canonical_cover()
let min_exact = pla.run_minimize_exact(true)
let min_exact_literals = pla.run_minimize_exact_literals(true)

printf "\n%A\n" canonical_cover
printf "\n%A\n" min_exact
printf "\n%A\n" min_exact_literals
