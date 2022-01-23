#!/usr/bin/env bash

valgrind --tool=callgrind  --callgrind-out-file=./callgrind.out ./main <input.txt

gprof2dot -f callgrind callgrind.out | dot -Tsvg -o output.svg

kcachegrind ./output.svg