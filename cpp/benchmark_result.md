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
 | funcA    |    40.75 μs |   400.20 μs |  4022.06 μs | 39991.60 μs | 
 | funcB    |    40.81 μs |   396.57 μs |  3998.64 μs | 38758.80 μs | 
 | funcC    |    39.60 μs |   403.35 μs |  3936.34 μs | 39997.60 μs | 
 | funcD    |    57.52 μs |   577.11 μs |  5664.42 μs | 54740.40 μs | 
 | funcE    |   120.44 μs |  1208.68 μs | 11943.42 μs | 115646.60 μs | 
 | funcF    |   106.58 μs |  1064.12 μs | 10551.26 μs | 103126.40 μs | 
 | funcG    |   131.78 μs |  1318.55 μs | 13069.44 μs | 130645.80 μs | 
 | funcH    |   131.26 μs |  1306.59 μs | 12904.12 μs | 131403.70 μs | 
 | funcI    |   107.54 μs |  1061.24 μs | 10638.78 μs | 110166.00 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |    46.69 μs |   411.45 μs |  4563.30 μs | 39079.50 μs | 
 | funcB    |    38.85 μs |   383.91 μs |  3857.78 μs | 38151.60 μs | 
 | funcC    |    38.60 μs |   381.91 μs |  3939.64 μs | 38469.70 μs | 
 | funcD    |    32.21 μs |   198.03 μs |  1749.62 μs | 17059.40 μs | 
 | funcE    |    38.71 μs |   196.64 μs |  1919.78 μs | 20084.90 μs | 
 | funcF    |    34.27 μs |   199.53 μs |  1885.78 μs | 18976.40 μs | 
 | funcG    |    38.84 μs |   196.71 μs |  1955.96 μs | 19570.90 μs | 
 | funcH    |    39.52 μs |   195.17 μs |  1794.38 μs | 18402.60 μs | 
 | funcI    |   106.03 μs |  1083.22 μs | 10654.08 μs | 107654.80 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     3.00 μs |    41.00 μs |  4007.00 μs | 
 | funcB    |     2.00 μs |    41.00 μs |  3847.00 μs | 
 | funcC    |     2.00 μs |    40.00 μs |  3911.00 μs | 
 | funcD    |     2.00 μs |    57.00 μs |  5600.00 μs | 
 | funcE    |     2.00 μs |   118.00 μs | 11789.00 μs | 
 | funcF    |     2.00 μs |   106.00 μs | 10405.00 μs | 
 | funcG    |     2.00 μs |   130.00 μs | 12906.00 μs | 
 | funcH    |     2.00 μs |   129.00 μs | 12684.00 μs | 
 | funcI    |     2.00 μs |   106.00 μs | 10474.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     3.00 μs |    42.00 μs |  4068.00 μs | 
 | funcB    |     2.00 μs |    40.00 μs |  3943.00 μs | 
 | funcC    |     1.00 μs |    39.00 μs |  4048.00 μs | 
 | funcD    |     2.00 μs |    33.00 μs |  1836.00 μs | 
 | funcE    |     2.00 μs |    40.00 μs |  1821.00 μs | 
 | funcF    |     2.00 μs |    36.00 μs |  1775.00 μs | 
 | funcG    |     2.00 μs |    40.00 μs |  1830.00 μs | 
 | funcH    |     2.00 μs |    41.00 μs |  1825.00 μs | 
 | funcI    |     2.00 μs |   109.00 μs | 11037.00 μs | 

 - ## Input Files - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     2.09 μs |    40.22 μs |  3895.77 μs | 
 | funcB    |     1.29 μs |    40.43 μs |  3855.72 μs | 
 | funcC    |     1.01 μs |    38.59 μs |  3897.16 μs | 
 | funcD    |     1.01 μs |    56.26 μs |  5543.30 μs | 
 | funcE    |     2.04 μs |   118.16 μs | 11851.63 μs | 
 | funcF    |     2.00 μs |   104.34 μs | 10444.72 μs | 
 | funcG    |     2.06 μs |   128.40 μs | 12927.88 μs | 
 | funcH    |     2.15 μs |   126.07 μs | 12616.98 μs | 
 | funcI    |     2.00 μs |   104.26 μs | 10435.56 μs | 

 - ## Input Files Sorted - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     2.00 μs |    40.39 μs |  3863.80 μs | 
 | funcB    |     1.41 μs |    38.38 μs |  3786.23 μs | 
 | funcC    |     1.00 μs |    37.25 μs |  3879.01 μs | 
 | funcD    |     1.02 μs |    28.28 μs |  1707.99 μs | 
 | funcE    |     2.04 μs |    27.62 μs |  1753.42 μs | 
 | funcF    |     2.00 μs |    30.86 μs |  1831.46 μs | 
 | funcG    |     2.00 μs |    28.01 μs |  1784.17 μs | 
 | funcH    |     2.00 μs |    27.74 μs |  1772.64 μs | 
 | funcI    |     2.00 μs |   104.77 μs | 10543.15 μs | 

# Benchmark Results: Built with `-std=c++17 -O3`

 - ## Internal Test Data
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |     5.84 μs |    57.12 μs |   578.34 μs |  6522.20 μs | 
 | funcB    |    21.85 μs |   220.06 μs |  2104.02 μs | 20774.20 μs | 
 | funcC    |     5.49 μs |    57.69 μs |   540.14 μs |  5554.10 μs | 
 | funcD    |    12.25 μs |   119.10 μs |  1192.10 μs | 11800.10 μs | 
 | funcE    |    21.36 μs |   218.82 μs |  2199.56 μs | 21898.20 μs | 
 | funcF    |    14.31 μs |   142.08 μs |  1419.20 μs | 14195.70 μs | 
 | funcG    |    21.49 μs |   218.27 μs |  2189.46 μs | 21813.90 μs | 
 | funcH    |    21.23 μs |   218.92 μs |  2188.74 μs | 21745.00 μs | 
 | funcI    |    20.74 μs |   211.34 μs |  2118.92 μs | 21211.40 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | :------- | ----------: | ----------: | ----------: | ----------: | 
 | funcA    |    16.27 μs |    64.75 μs |   479.82 μs |  4727.50 μs | 
 | funcB    |     9.12 μs |    81.17 μs |   698.62 μs |  6906.10 μs | 
 | funcC    |    10.07 μs |    62.45 μs |   478.00 μs |  4788.50 μs | 
 | funcD    |    10.06 μs |    41.42 μs |   361.02 μs |  3613.00 μs | 
 | funcE    |    11.07 μs |    52.21 μs |   474.64 μs |  4758.40 μs | 
 | funcF    |    10.02 μs |    41.75 μs |   362.26 μs |  3648.90 μs | 
 | funcG    |    11.29 μs |    51.46 μs |   470.04 μs |  4729.90 μs | 
 | funcH    |    11.00 μs |    53.18 μs |   472.74 μs |  4712.20 μs | 
 | funcI    |    22.21 μs |   221.65 μs |  2059.62 μs | 20615.30 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |        0 μs |     6.00 μs |   571.00 μs | 
 | funcB    |        0 μs |    15.00 μs |  1467.00 μs | 
 | funcC    |        0 μs |     6.00 μs |   516.00 μs | 
 | funcD    |        0 μs |    12.00 μs |  1151.00 μs | 
 | funcE    |        0 μs |    21.00 μs |  2135.00 μs | 
 | funcF    |        0 μs |    14.00 μs |  1379.00 μs | 
 | funcG    |        0 μs |    21.00 μs |  2123.00 μs | 
 | funcH    |        0 μs |    21.00 μs |  2161.00 μs | 
 | funcI    |        0 μs |    20.00 μs |  2063.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |        0 μs |    16.00 μs |   487.00 μs | 
 | funcB    |        0 μs |     9.00 μs |   699.00 μs | 
 | funcC    |        0 μs |    10.00 μs |   489.00 μs | 
 | funcD    |        0 μs |    10.00 μs |   352.00 μs | 
 | funcE    |        0 μs |    11.00 μs |   456.00 μs | 
 | funcF    |        0 μs |    10.00 μs |   345.00 μs | 
 | funcG    |        0 μs |     8.00 μs |   468.00 μs | 
 | funcH    |        0 μs |     6.00 μs |   465.00 μs | 
 | funcI    |        0 μs |    22.00 μs |  2091.00 μs | 

 - ## Input Files - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     0.01 μs |     5.12 μs |   553.54 μs | 
 | funcB    |        0 μs |     8.72 μs |  1406.53 μs | 
 | funcC    |        0 μs |     6.85 μs |   542.77 μs | 
 | funcD    |        0 μs |    11.81 μs |  1159.99 μs | 
 | funcE    |        0 μs |    21.05 μs |  2121.98 μs | 
 | funcF    |        0 μs |    14.16 μs |  1375.58 μs | 
 | funcG    |        0 μs |    21.02 μs |  2138.88 μs | 
 | funcH    |        0 μs |    21.30 μs |  2134.64 μs | 
 | funcI    |        0 μs |    20.05 μs |  2084.02 μs | 

 - ## Input Files Sorted - Run 100x Each
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | :------- | ----------: | ----------: | ----------: | 
 | funcA    |     0.01 μs |    14.97 μs |   474.40 μs | 
 | funcB    |        0 μs |     9.15 μs |   697.87 μs | 
 | funcC    |        0 μs |    10.00 μs |   469.82 μs | 
 | funcD    |        0 μs |     4.13 μs |   346.24 μs | 
 | funcE    |        0 μs |     5.10 μs |   458.06 μs | 
 | funcF    |        0 μs |     4.09 μs |   346.53 μs | 
 | funcG    |        0 μs |     5.15 μs |   458.65 μs | 
 | funcH    |        0 μs |     5.00 μs |   462.79 μs | 
 | funcI    |        0 μs |    22.10 μs |  2077.07 μs | 

 ### --- End ---
