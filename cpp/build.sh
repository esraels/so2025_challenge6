#!/bin/bash
if [ "$#" -gt 0 ]; then
    compile_options=$*
else
    compile_options='-std=c++17 -O3'
fi
g++ main.cpp -o out/app $compile_options