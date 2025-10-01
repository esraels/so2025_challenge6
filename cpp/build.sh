#!/bin/bash
if [ "$#" -gt 0 ]; then
    compile_options=$*
else
    compile_options='-std=c++17 -O3'
fi

if ! [ -d "out" ]; then mkdir out; fi

g++ main.cpp -o out/app $compile_options