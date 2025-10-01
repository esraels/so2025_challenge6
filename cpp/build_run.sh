#!/bin/bash
#g++ main.cpp -o out/app -std=c++17 || exit 1
#g++ main.cpp -o out/app -std=c++17 -O2 || exit 1
g++ main.cpp -o out/app -std=c++17 -O3 || exit 1



#./out/app $*
cd input
../out/app $*  100_nums.txt 10k_nums.txt 1M_nums.txt
cd ..