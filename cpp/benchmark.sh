#!/bin/bash

result_file=result_benchmark.md

input_files=(
    'input/100_nums.txt'
    'input/10k_nums.txt' 
    'input/1M_nums.txt'
    #'"sample with space.txt"'
)

compile_options=(
    #'-std=c++11 -O0'  # build error
    #'-std=c++11 -O3'  # build error
    '-std=c++17 -O0'
    '-std=c++17 -O3'
    '-std=c++20 -O0'
    '-std=c++20 -O3'
)

benchmark_titles=(
    "Internal Test Data"
    "Internal Test Data Sorted"
    "Input Files"
    "Input Files Sorted"
    "Input Files - Run 100x Each"
    "Input Files Sorted - Run 100x Each"
)

benchmark_options=(
    "-t "
    "-t -s"
    "-t ${input_files[*]}"
    "-t ${input_files[*]} -s"
    "-t ${input_files[*]} -n 100"
    "-t ${input_files[*]} -n 100 -s"
)

echo -e "# Benchmark: \n\n"

echo -e " - ### The Test Functions: \n"
./build.sh          || exit $?
./run_app.sh -f -t  || exit $?

for build_setup in "${compile_options[@]}"; do
    echo -e "\n# Benchmark Results: Built with \`$build_setup\`"
    for i in "${!benchmark_options[@]}"; do
        echo -e "\n - ## ${benchmark_titles[$i]}"
        ./build.sh $build_setup                 || exit $?
        ./run_app.sh ${benchmark_options[$i]}   || exit $?
    done
done

echo -e "\n ### --- End ---"
exit 0