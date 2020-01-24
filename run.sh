#!/bin/bash

# Assignment 1 run script

# Mapper test
# gcc mapper.c -o mapper
# ./mapper input.txt  

# Combiner test
gcc mapper.c -o mapper
gcc reducer.c -o reducer
gcc combiner.c -o combiner

./combiner input.txt