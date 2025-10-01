
# My Entry for SO 2025 Code Challenge #6: Int Counting
- Jump to **[The Result](#the-result):** section for the actual benchmarking result.
- The code in this project are not written by AI. Sometimes, `VS Code`'s AI confuses me while typing but I keep on canceling it's suggested code. I am surprised that some of its suggestion are what I actually want to code, even those derivation of boolean algebra formulas I did in the code comments! There are times I messed around with it if it will actually produces correct code or comments. It is like playing with somebody while in the middle of a work with deadline. I am not sure if I wasted my time playing with it, but I kinda felt satisfied and had fun.

- ### Code Structure:
    - I provided different version of test functions with incremental code optimization changes to check whether those changes really improved the execution time. Surprised me... it is not always the case! It depends a lot on how the numbers are arranged in the list.
    - I added some command line options to tweak the program's behavior so I can test and check on different setup without modifying a lot in the code each time.
        - Just add `-?` in the command line argument to see the mini help document.
    - The app generates internal test data with 10x larger than the 1M list of numbers provided in the [stackoverflow](https://stackoverflow.com/beta/challenges/79766578/code-challenge-6-integer-counting) code challenge page.
    - The Logs format are in `markdown` syntax so you can pipe the output to a markdown file and view the output in a markdown viewer. I use `VS Code`'s builtin markdown viewer.
    - The test functions so far are optimize for **SPEED**. I haven't got the time to finish the optimize for **SPACE** version of functions before the submission day. Please refer to the _todo_list.txt_ to see what was my full plan before starting to code in this project.
    - `funcA` is the basis to check if the other functions got the correct answers.

- ### Build Scripts:
    - I used `bash` scripts for building the app and manipulating the output. I am running and testing the app `WSL2`. I planned to provide `batch` scripts version so the app will be buildable and testable in Windows but I have no time. The deadline is today, as of this writing (Sept 30, 2025... 🤔). Wait... it is actually Oct 01 now, yesterday is the deadline. Oh no... ;-(. Anyway, it seems that I can still submit it and Sept 30 will be the day the other entries are visible. It feels like the deadline because it is a chance to copy other works or based your work from them. I don't wanna look! 🫣 I am not even sure if I misunderstood the instructions and actually submitting a completely wrong entry. 🐒
    - I provided below scripts for easier build and testing:
        - `./build.sh [OPTIONS]`: 
            - Just build it, no run. `OPTIONS` are for `g++` arguments.
        - `./run_app.sh [OPTIONS] > result.md`: 
            - Just run it. `OPTIONS` are for the app's arguments.
        - `./build_run.sh [OPTIONS] > result.md`: 
            - For the lazy people, build and then run. `OPTIONS` are for the app arguments.
        - `./benchmark.sh > result.md`: 
            - The actual benchmark where you can tweak what test options and input to use.
            - Just open this file to customize what to test and benchmark.
    - Some samples you can try in the terminal:
        ```bash
        cd cpp
        ./build_run.sh -f -t
        ./build_run.sh -n 1000 -s > result.md
        ./build_run.sh -s
        ./run_app.sh -n 10 input/1M_nums.txt
        ./run_app.sh -n 10 -s input/1M_nums.txt
        ./run_app.sh -n 10 -s -d -t input/1M_nums.txt
        ./run_app.sh -n 10 -s -d -t input/1M_nums.txt input/10k_nums.txt
        ./build.sh
        ./build_run.sh
        ./build_run.sh -t
        ./build_run.sh -t input/1M_nums.txt input/10k_nums.txt
        ./build_run.sh -t input/1M_nums.txt input/10k_nums.txt > result.md
        ./build_run.sh --no-verbose
        ./build.sh one two
        ./build.sh -std=c++20
        ./build.sh -std=c++20 -O1
        ./build.sh -std=c++17 -O3
        ./build_run.sh
        ./run_app.sh -h
        ./run_app.sh -h -s
        ./build_run.sh -n 10
        ./build_run.sh -n -5
        ./build_run.sh -n --5
        ./build_run.sh -n " 9"
        ./build_run.sh -n " -9"
        ./build_run.sh -n 0
        ./build_run.sh -n 100k
        ./build_run.sh -n 100k.txt
        ./build_run.sh -n 100k.txasdfasdfadfasdft        
        ./run_app.sh -n 1000 input/10k_nums.txt
        ./run_app.sh -n 100 input/1M_nums.txt
        ./run_app.sh -n 100 input/1M_nums.txt -s
        ./run_app.sh -n 100 input/1M_nums.txt -s -d
        ./build.sh
        ./build.sh -std=c++14
        ./build.sh -std=c++14 -Os
        ./run_app.sh -n 100 -t -d input/10k_nums.txt
        ./run_app.sh -n 100 -t -d input/10k_nums.txt > result.md
        ./build_run.sh
        ./build_run.sh -s
        ./build_run.sh -t
        ./build_run.sh -t -n 10
        ./build_run.sh -t -n 10 -s
        ./build_run.sh -t -n 10 -s
        ./build.sh " "
        ./build_run.sh -f
        ./run_app.sh -f
        ./run_app.sh -f -v
        ./run_app.sh -v -f
        ./run_app.sh -t -f
        ./run_app.sh -f -t > result.md
        ./benchmark.sh
        ./benchmark.sh > result.md
        ./benchmark.sh > benchmark_result.md
        ./build_run.sh -t
        ./build_run.sh -t > result.md
        ./build_run.sh -t input/100_nums.txt input/10k_nums.txt input/1M_nums.txt
        ./build_run.sh -t input/100_nums.txt input/10k_nums.txt input/1M_nums.txt > result.md
        ```
        - Yeah, you got it right where was this came from. Look what I had been through! This was an adventure!
            - (to those who didn't get it, it's from bash history. I just got lazy to choose... It's submission day! ~🏃‍➡️🥷)

---

## The Result:
- Below is a an sample generated result of this app.
- You can see that the optimize version of functions is slower than the unoptimized version when the input data is purely random.
- In my conclusion, it really pays well if the input data is normalized before processing. In this case, "sorted".
- For the unoptimized version, the execution time is consistent whether the data is sorted or not.

# Benchmark: 

 - ### The Test Functions: 

 |   name   | Description 
 | :------- | :-------------------------------- | 
 | funcA    |  unoptimized. basis for correct results.
 | funcB    |  like funcA but search maxcount starting from iMin.
 | funcC    |  like funcB but now, search upto iMax only.
 | funcD    |  like funcC but counting ahead consecutive same numbers.
 | funcE    |  like funcD but converted most conditional branches to branchless version.
 | funcF    |  like funcE but converted back the branches that uses `&&`, and `||`.
 | funcG    |  like funcE but remove all `const` specifier of vars inside the loops.
 | funcH    |  like funcE but changed the inside loop from `while` to `for`.
 | funcI    |  like funcE but removed counting ahead of consecutive same numbers.

# Benchmark Results: Built with `-std=c++17 -O0`

 - ## Internal Test Data
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |    74.26 μs |   745.47 μs |  7428.84 μs | 73561.40 μs | 
 | funcB    |    80.03 μs |   791.83 μs |  7721.04 μs | 78017.30 μs | 
 | funcC    |    79.06 μs |   796.73 μs |  7846.02 μs | 78641.80 μs | 
 | funcD    |   120.02 μs |  1156.56 μs | 12282.96 μs | 118367.00 μs | 
 | funcE    |   194.08 μs |  2015.10 μs | 19627.04 μs | 196977.60 μs | 
 | funcF    |   143.83 μs |  1845.10 μs | 18483.40 μs | 250449.70 μs | 
 | funcG    |   213.96 μs |  2123.48 μs | 21186.08 μs | 208001.90 μs | 
 | funcH    |   217.32 μs |  2154.06 μs | 21092.36 μs | 211048.90 μs | 
 | funcI    |   176.19 μs |  1742.70 μs | 17104.34 μs | 167712.30 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |    77.98 μs |   712.10 μs |  7144.98 μs | 71321.30 μs | 
 | funcB    |    77.65 μs |   700.96 μs |  7381.24 μs | 72708.50 μs | 
 | funcC    |    75.08 μs |   768.81 μs |  7663.18 μs | 76149.70 μs | 
 | funcD    |    55.66 μs |   389.98 μs |  3595.98 μs | 35389.20 μs | 
 | funcE    |    66.27 μs |   395.69 μs |  3505.18 μs | 34926.30 μs | 
 | funcF    |    59.97 μs |   408.87 μs |  3776.52 μs | 35969.50 μs | 
 | funcG    |    68.48 μs |   352.35 μs |  3453.20 μs | 34613.80 μs | 
 | funcH    |    66.69 μs |   373.08 μs |  3374.40 μs | 34828.70 μs | 
 | funcI    |   168.31 μs |  1665.87 μs | 16829.46 μs | 167069.50 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     5.00 μs |    67.00 μs |  6762.00 μs | 
 | funcB    |     3.00 μs |    70.00 μs |  7240.00 μs | 
 | funcC    |     3.00 μs |    71.00 μs |  7684.00 μs | 
 | funcD    |     3.00 μs |   116.00 μs | 11704.00 μs | 
 | funcE    |     3.00 μs |   169.00 μs | 19779.00 μs | 
 | funcF    |     4.00 μs |   156.00 μs | 18910.00 μs | 
 | funcG    |     4.00 μs |   207.00 μs | 20267.00 μs | 
 | funcH    |     3.00 μs |   224.00 μs | 19642.00 μs | 
 | funcI    |     3.00 μs |   151.00 μs | 16841.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     5.00 μs |    72.00 μs |  7253.00 μs | 
 | funcB    |     4.00 μs |    75.00 μs |  7310.00 μs | 
 | funcC    |     3.00 μs |    75.00 μs |  7762.00 μs | 
 | funcD    |     3.00 μs |    53.00 μs |  3579.00 μs | 
 | funcE    |     4.00 μs |    66.00 μs |  3561.00 μs | 
 | funcF    |     4.00 μs |    57.00 μs |  3560.00 μs | 
 | funcG    |     4.00 μs |    62.00 μs |  3569.00 μs | 
 | funcH    |     4.00 μs |    61.00 μs |  3659.00 μs | 
 | funcI    |     4.00 μs |   163.00 μs | 16387.00 μs | 

 - ## Input Files - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     3.78 μs |    75.71 μs |  7318.57 μs | 
 | funcB    |     3.17 μs |    80.07 μs |  7470.47 μs | 
 | funcC    |     2.04 μs |    78.61 μs | 14980.85 μs | 
 | funcD    |     2.37 μs |   121.00 μs | 12040.17 μs | 
 | funcE    |     3.01 μs |   194.35 μs | 19348.97 μs | 
 | funcF    |     3.74 μs |   178.50 μs | 17877.13 μs | 
 | funcG    |     3.13 μs |   206.86 μs | 20894.38 μs | 
 | funcH    |     3.09 μs |   214.09 μs | 20939.77 μs | 
 | funcI    |     3.34 μs |   175.79 μs | 17027.47 μs | 

 - ## Input Files Sorted - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     4.75 μs |    78.92 μs |  7156.21 μs | 
 | funcB    |     3.60 μs |    75.66 μs |  7336.48 μs | 
 | funcC    |     2.45 μs |    79.15 μs |  7674.38 μs | 
 | funcD    |     2.78 μs |    54.46 μs |  3811.29 μs | 
 | funcE    |     4.17 μs |    58.00 μs |  3518.76 μs | 
 | funcF    |     3.02 μs |    60.02 μs |  3761.61 μs | 
 | funcG    |     3.12 μs |    58.11 μs |  3565.37 μs | 
 | funcH    |     4.44 μs |    61.17 μs |  3574.91 μs | 
 | funcI    |     3.51 μs |   177.65 μs | 16731.20 μs | 

# Benchmark Results: Built with `-std=c++17 -O3`

 - ## Internal Test Data
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |    12.98 μs |   127.43 μs |  1294.88 μs | 13289.10 μs | 
 | funcB    |    32.03 μs |   300.63 μs |  3072.36 μs | 29541.20 μs | 
 | funcC    |    13.43 μs |   136.94 μs |  1367.16 μs | 13977.60 μs | 
 | funcD    |    34.15 μs |   384.90 μs |  3215.48 μs | 32806.40 μs | 
 | funcE    |    35.69 μs |   350.45 μs |  3721.40 μs | 36802.70 μs | 
 | funcF    |    36.57 μs |   349.65 μs |  3336.06 μs | 36215.10 μs | 
 | funcG    |    36.02 μs |   361.99 μs |  3763.10 μs | 37554.60 μs | 
 | funcH    |    36.52 μs |   359.46 μs |  3644.96 μs | 36718.60 μs | 
 | funcI    |    33.26 μs |   293.15 μs |  3238.12 μs | 34710.40 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |    19.71 μs |   155.93 μs |  1241.98 μs | 12754.20 μs | 
 | funcB    |    18.79 μs |   187.89 μs |  1733.02 μs | 17893.50 μs | 
 | funcC    |    15.03 μs |   147.79 μs |  1317.16 μs | 13302.60 μs | 
 | funcD    |    16.06 μs |    75.89 μs |   695.16 μs |  7425.90 μs | 
 | funcE    |    19.71 μs |   123.51 μs |  1170.90 μs | 12020.30 μs | 
 | funcF    |    16.41 μs |    76.79 μs |   695.68 μs |  7230.10 μs | 
 | funcG    |    19.39 μs |   123.29 μs |  1196.06 μs | 12149.20 μs | 
 | funcH    |    19.99 μs |   123.35 μs |  1193.00 μs | 12297.80 μs | 
 | funcI    |    36.60 μs |   337.31 μs |  3205.24 μs | 32053.20 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     1.00 μs |    12.00 μs |  1197.00 μs | 
 | funcB    |     1.00 μs |    22.00 μs |  2271.00 μs | 
 | funcC    |        0 μs |    13.00 μs |  1350.00 μs | 
 | funcD    |        0 μs |    30.00 μs |  3199.00 μs | 
 | funcE    |        0 μs |    33.00 μs |  3437.00 μs | 
 | funcF    |     1.00 μs |    33.00 μs |  3536.00 μs | 
 | funcG    |        0 μs |    32.00 μs |  3498.00 μs | 
 | funcH    |        0 μs |    32.00 μs |  3620.00 μs | 
 | funcI    |        0 μs |    30.00 μs |  3348.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     1.00 μs |    18.00 μs |  1249.00 μs | 
 | funcB    |     1.00 μs |    18.00 μs |  1836.00 μs | 
 | funcC    |        0 μs |    14.00 μs |  1417.00 μs | 
 | funcD    |        0 μs |    14.00 μs |   799.00 μs | 
 | funcE    |     1.00 μs |    18.00 μs |  1219.00 μs | 
 | funcF    |        0 μs |    15.00 μs |   665.00 μs | 
 | funcG    |        0 μs |    15.00 μs |  1168.00 μs | 
 | funcH    |        0 μs |    12.00 μs |  1180.00 μs | 
 | funcI    |        0 μs |    34.00 μs |  3159.00 μs | 

 - ## Input Files - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     0.01 μs |    12.23 μs |  1307.64 μs | 
 | funcB    |     1.00 μs |    17.17 μs |  2412.52 μs | 
 | funcC    |        0 μs |    13.30 μs |  1258.40 μs | 
 | funcD    |        0 μs |    33.63 μs |  3271.69 μs | 
 | funcE    |        0 μs |    36.18 μs |  3766.19 μs | 
 | funcF    |     0.01 μs |    36.04 μs |  3613.89 μs | 
 | funcG    |        0 μs |    35.21 μs |  3714.58 μs | 
 | funcH    |     0.01 μs |    35.11 μs |  3757.49 μs | 
 | funcI    |     0.42 μs |    32.77 μs |  3494.65 μs | 

 - ## Input Files Sorted - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     0.01 μs |    18.00 μs |  1122.91 μs | 
 | funcB    |     1.00 μs |    17.97 μs |  1756.84 μs | 
 | funcC    |        0 μs |    14.06 μs |  1324.73 μs | 
 | funcD    |        0 μs |     8.84 μs |   678.32 μs | 
 | funcE    |     0.01 μs |    12.52 μs |  1227.68 μs | 
 | funcF    |     0.01 μs |     8.54 μs |   689.60 μs | 
 | funcG    |        0 μs |    12.15 μs |  1221.19 μs | 
 | funcH    |        0 μs |    13.05 μs |  1197.38 μs | 
 | funcI    |        0 μs |    35.84 μs |  3203.73 μs | 

 ### --- End ---
