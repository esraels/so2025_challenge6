# Benchmark: 


 - ### The Test Functions: 

 |   name   | Description 
 | -------- | --------------------------------- | 
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
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    73.87 μs |   696.70 μs |  7009.20 μs | 71286.10 μs | 
 | funcB    |    77.37 μs |   752.94 μs |  7283.46 μs | 73385.00 μs | 
 | funcC    |    77.42 μs |   754.02 μs |  7489.34 μs | 75674.10 μs | 
 | funcD    |   117.03 μs |  1171.52 μs | 11605.18 μs | 116075.70 μs | 
 | funcE    |   185.37 μs |  1830.77 μs | 18575.20 μs | 191798.90 μs | 
 | funcF    |   179.81 μs |  1727.56 μs | 20056.42 μs | 181270.20 μs | 
 | funcG    |   172.21 μs |  2006.37 μs | 20720.42 μs | 206995.80 μs | 
 | funcH    |   192.08 μs |  2000.99 μs | 20015.66 μs | 205266.10 μs | 
 | funcI    |   160.63 μs |  1667.81 μs | 16463.04 μs | 216350.50 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    76.65 μs |   755.84 μs |  7304.70 μs | 72618.60 μs | 
 | funcB    |    77.45 μs |   750.72 μs |  7539.30 μs | 74405.00 μs | 
 | funcC    |    77.39 μs |   768.57 μs |  7454.30 μs | 74216.50 μs | 
 | funcD    |    55.41 μs |   375.23 μs |  3520.48 μs | 33820.00 μs | 
 | funcE    |    66.52 μs |   385.98 μs |  3412.40 μs | 34460.90 μs | 
 | funcF    |    60.08 μs |   408.45 μs |  3524.78 μs | 36642.80 μs | 
 | funcG    |    67.12 μs |   390.47 μs |  3411.10 μs | 34859.70 μs | 
 | funcH    |    68.48 μs |   397.67 μs |  3353.04 μs | 35998.50 μs | 
 | funcI    |   165.61 μs |  1709.01 μs | 16875.22 μs | 168553.10 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     5.00 μs |    68.00 μs |  6975.00 μs | 
 | funcB    |     3.00 μs |    95.00 μs |  7327.00 μs | 
 | funcC    |     3.00 μs |    69.00 μs |  8101.00 μs | 
 | funcD    |     3.00 μs |   115.00 μs | 12320.00 μs | 
 | funcE    |     3.00 μs |   186.00 μs | 19371.00 μs | 
 | funcF    |     3.00 μs |   194.00 μs | 14779.00 μs | 
 | funcG    |     3.00 μs |   191.00 μs | 20507.00 μs | 
 | funcH    |     4.00 μs |   179.00 μs | 20380.00 μs | 
 | funcI    |     3.00 μs |   150.00 μs | 16746.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     5.00 μs |    71.00 μs |  7394.00 μs | 
 | funcB    |     4.00 μs |    76.00 μs |  8497.00 μs | 
 | funcC    |     3.00 μs |    75.00 μs |  7483.00 μs | 
 | funcD    |     4.00 μs |    53.00 μs |  3651.00 μs | 
 | funcE    |     4.00 μs |    65.00 μs |  3631.00 μs | 
 | funcF    |     4.00 μs |    58.00 μs |  3626.00 μs | 
 | funcG    |     4.00 μs |    64.00 μs |  3221.00 μs | 
 | funcH    |     4.00 μs |    64.00 μs |  2251.00 μs | 
 | funcI    |     3.00 μs |   164.00 μs | 16237.00 μs | 

 - ## Input Files - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     3.72 μs |    73.64 μs |  7270.44 μs | 
 | funcB    |     3.27 μs |    79.68 μs |  8236.07 μs | 
 | funcC    |     2.12 μs |    78.53 μs |  8330.67 μs | 
 | funcD    |     2.77 μs |   121.40 μs | 12067.03 μs | 
 | funcE    |     3.07 μs |   198.31 μs | 19720.85 μs | 
 | funcF    |     3.03 μs |   185.54 μs | 17908.05 μs | 
 | funcG    |     3.21 μs |   212.41 μs | 20739.83 μs | 
 | funcH    |     3.04 μs |   167.77 μs | 26074.18 μs | 
 | funcI    |     3.05 μs |   171.88 μs | 16865.38 μs | 

 - ## Input Files Sorted - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     4.01 μs |    75.62 μs |  7370.81 μs | 
 | funcB    |     4.17 μs |    77.99 μs |  7345.35 μs | 
 | funcC    |     2.51 μs |    80.23 μs |  7674.79 μs | 
 | funcD    |     3.26 μs |    53.43 μs |  3579.84 μs | 
 | funcE    |     3.16 μs |    58.73 μs |  3565.42 μs | 
 | funcF    |     3.18 μs |    57.19 μs |  3684.73 μs | 
 | funcG    |     3.73 μs |    35.49 μs |  3519.50 μs | 
 | funcH    |     3.35 μs |    33.63 μs |  3644.75 μs | 
 | funcI    |     4.09 μs |   170.66 μs | 16918.66 μs | 

# Benchmark Results: Built with `-std=c++17 -O3`

 - ## Internal Test Data
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    10.46 μs |    71.37 μs |  1264.98 μs | 13531.30 μs | 
 | funcB    |    23.60 μs |   274.11 μs |  2466.98 μs | 26103.00 μs | 
 | funcC    |     9.45 μs |    93.61 μs |   769.74 μs |  9226.70 μs | 
 | funcD    |    14.56 μs |   185.62 μs |  1669.60 μs | 19652.70 μs | 
 | funcE    |    27.67 μs |   254.57 μs |  2678.04 μs | 28325.20 μs | 
 | funcF    |    19.76 μs |   163.62 μs |  1784.02 μs | 17280.70 μs | 
 | funcG    |    30.48 μs |   239.99 μs |  2654.98 μs | 25454.40 μs | 
 | funcH    |    31.20 μs |   288.21 μs |  2935.98 μs | 27634.40 μs | 
 | funcI    |    22.57 μs |   237.61 μs |  2988.26 μs | 32287.60 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    15.54 μs |    78.56 μs |   556.12 μs |  5596.70 μs | 
 | funcB    |    13.08 μs |    84.40 μs |   805.54 μs |  7826.40 μs | 
 | funcC    |    10.37 μs |    76.05 μs |   565.92 μs |  5677.40 μs | 
 | funcD    |    10.33 μs |    45.24 μs |   441.16 μs |  3865.10 μs | 
 | funcE    |    11.11 μs |    53.77 μs |   535.04 μs |  5124.70 μs | 
 | funcF    |    10.13 μs |    51.74 μs |   443.98 μs |  3975.40 μs | 
 | funcG    |    11.02 μs |    54.26 μs |   529.76 μs |  5073.70 μs | 
 | funcH    |    11.18 μs |    53.16 μs |   543.74 μs |  5181.00 μs | 
 | funcI    |    22.77 μs |   231.39 μs |  2169.32 μs | 21528.40 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |        0 μs |     6.00 μs |   577.00 μs | 
 | funcB    |        0 μs |    16.00 μs |  1440.00 μs | 
 | funcC    |        0 μs |     6.00 μs |   521.00 μs | 
 | funcD    |        0 μs |    12.00 μs |  1187.00 μs | 
 | funcE    |        0 μs |    21.00 μs |  2191.00 μs | 
 | funcF    |        0 μs |    15.00 μs |  1415.00 μs | 
 | funcG    |        0 μs |    21.00 μs |  2191.00 μs | 
 | funcH    |        0 μs |    21.00 μs |  2213.00 μs | 
 | funcI    |        0 μs |    21.00 μs |  2159.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |        0 μs |    15.00 μs |   498.00 μs | 
 | funcB    |        0 μs |     9.00 μs |   700.00 μs | 
 | funcC    |        0 μs |    10.00 μs |   488.00 μs | 
 | funcD    |        0 μs |    10.00 μs |   348.00 μs | 
 | funcE    |        0 μs |    11.00 μs |   467.00 μs | 
 | funcF    |        0 μs |    11.00 μs |   350.00 μs | 
 | funcG    |        0 μs |     9.00 μs |   464.00 μs | 
 | funcH    |        0 μs |     6.00 μs |   475.00 μs | 
 | funcI    |        0 μs |    22.00 μs |  2088.00 μs | 

 - ## Input Files - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |        0 μs |     5.54 μs |   581.47 μs | 
 | funcB    |        0 μs |     9.01 μs |  1473.49 μs | 
 | funcC    |        0 μs |     5.01 μs |   560.23 μs | 
 | funcD    |        0 μs |    12.52 μs |  1192.82 μs | 
 | funcE    |        0 μs |    21.49 μs |  2202.36 μs | 
 | funcF    |        0 μs |    14.13 μs |  1426.34 μs | 
 | funcG    |        0 μs |    21.68 μs |  2213.90 μs | 
 | funcH    |        0 μs |    21.35 μs |  2275.83 μs | 
 | funcI    |        0 μs |    20.42 μs |  2219.16 μs | 

 - ## Input Files Sorted - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |        0 μs |    15.27 μs |   506.81 μs | 
 | funcB    |        0 μs |     9.06 μs |   742.12 μs | 
 | funcC    |        0 μs |    10.18 μs |   506.31 μs | 
 | funcD    |        0 μs |     4.54 μs |   361.66 μs | 
 | funcE    |        0 μs |     5.43 μs |   477.73 μs | 
 | funcF    |        0 μs |     4.17 μs |   370.34 μs | 
 | funcG    |        0 μs |     5.02 μs |   484.47 μs | 
 | funcH    |        0 μs |     5.07 μs |   470.24 μs | 
 | funcI    |        0 μs |    23.27 μs |  2094.36 μs | 

# Benchmark Results: Built with `-std=c++20 -O0`

 - ## Internal Test Data
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    43.35 μs |   426.63 μs |  4162.68 μs | 37782.10 μs | 
 | funcB    |    42.89 μs |   413.40 μs |  4061.54 μs | 45931.80 μs | 
 | funcC    |    41.48 μs |   395.61 μs |  3984.92 μs | 66628.70 μs | 
 | funcD    |    59.42 μs |   595.83 μs |  5946.18 μs | 123408.50 μs | 
 | funcE    |   128.21 μs |  1278.60 μs | 12810.36 μs | 190114.50 μs | 
 | funcF    |   112.24 μs |  1087.69 μs | 10775.94 μs | 177445.30 μs | 
 | funcG    |   129.99 μs |  1269.08 μs | 12695.10 μs | 203504.80 μs | 
 | funcH    |   126.67 μs |  1271.25 μs | 11974.10 μs | 199237.70 μs | 
 | funcI    |   112.77 μs |  1132.20 μs | 10297.50 μs | 171562.10 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    80.49 μs |   730.34 μs |  7230.50 μs | 71456.40 μs | 
 | funcB    |    81.45 μs |   801.62 μs |  7667.66 μs | 77652.90 μs | 
 | funcC    |    80.33 μs |   795.93 μs |  7560.08 μs | 76485.00 μs | 
 | funcD    |    60.44 μs |   347.04 μs |  3642.86 μs | 37636.70 μs | 
 | funcE    |    69.12 μs |   373.83 μs |  3502.70 μs | 34267.30 μs | 
 | funcF    |    71.45 μs |   484.88 μs |  4681.32 μs | 43677.90 μs | 
 | funcG    |    67.33 μs |   395.17 μs |  3481.74 μs | 34465.80 μs | 
 | funcH    |    68.05 μs |   414.99 μs |  3648.44 μs | 36251.60 μs | 
 | funcI    |   171.14 μs |  1731.56 μs | 17102.96 μs | 173472.00 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     4.00 μs |    70.00 μs |  7247.00 μs | 
 | funcB    |     4.00 μs |   197.00 μs |  8203.00 μs | 
 | funcC    |     3.00 μs |    71.00 μs |  8371.00 μs | 
 | funcD    |     3.00 μs |   155.00 μs | 13215.00 μs | 
 | funcE    |     3.00 μs |   307.00 μs | 21522.00 μs | 
 | funcF    |     4.00 μs |   174.00 μs | 19193.00 μs | 
 | funcG    |     4.00 μs |   187.00 μs | 21622.00 μs | 
 | funcH    |     3.00 μs |   192.00 μs | 21764.00 μs | 
 | funcI    |     3.00 μs |   161.00 μs | 17238.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     5.00 μs |    71.00 μs |  7417.00 μs | 
 | funcB    |     4.00 μs |    75.00 μs |  7824.00 μs | 
 | funcC    |     3.00 μs |    75.00 μs |  7973.00 μs | 
 | funcD    |     3.00 μs |    55.00 μs |  3976.00 μs | 
 | funcE    |     4.00 μs |    67.00 μs |  3664.00 μs | 
 | funcF    |     4.00 μs |    60.00 μs |  4037.00 μs | 
 | funcG    |     4.00 μs |    67.00 μs |  3611.00 μs | 
 | funcH    |     4.00 μs |   114.00 μs |  3825.00 μs | 
 | funcI    |     4.00 μs |   187.00 μs | 17917.00 μs | 

 - ## Input Files - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     3.60 μs |    80.58 μs |  7200.19 μs | 
 | funcB    |     3.01 μs |    86.06 μs |  7764.26 μs | 
 | funcC    |     2.29 μs |    82.25 μs |  7902.02 μs | 
 | funcD    |     2.75 μs |    85.89 μs | 12172.85 μs | 
 | funcE    |     3.59 μs |   212.06 μs | 19708.97 μs | 
 | funcF    |     3.32 μs |   187.02 μs | 12853.10 μs | 
 | funcG    |     3.22 μs |   216.97 μs | 16358.87 μs | 
 | funcH    |     3.50 μs |   210.01 μs | 28042.90 μs | 
 | funcI    |     3.29 μs |   172.31 μs | 17318.53 μs | 

 - ## Input Files Sorted - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     4.01 μs |    76.05 μs |  7220.23 μs | 
 | funcB    |     3.61 μs |    78.82 μs |  7971.77 μs | 
 | funcC    |     3.58 μs |    76.36 μs |  7864.10 μs | 
 | funcD    |     2.99 μs |    54.02 μs |  4008.93 μs | 
 | funcE    |     4.12 μs |    53.83 μs |  3507.44 μs | 
 | funcF    |     3.51 μs |    66.51 μs |  4581.09 μs | 
 | funcG    |     3.42 μs |    58.44 μs |  3660.93 μs | 
 | funcH    |     3.46 μs |    54.70 μs |  3770.57 μs | 
 | funcI    |     3.91 μs |   175.25 μs | 17406.94 μs | 

# Benchmark Results: Built with `-std=c++20 -O3`

 - ## Internal Test Data
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    16.91 μs |   154.02 μs |  1560.14 μs | 17037.00 μs | 
 | funcB    |    31.09 μs |   289.89 μs |  2834.00 μs | 29298.40 μs | 
 | funcC    |    14.23 μs |   124.48 μs |  1252.66 μs | 12736.90 μs | 
 | funcD    |    17.91 μs |   168.60 μs |  1782.20 μs | 17850.50 μs | 
 | funcE    |    36.91 μs |   334.74 μs |  3661.24 μs | 37056.40 μs | 
 | funcF    |    41.48 μs |   362.42 μs |  3709.56 μs | 36028.40 μs | 
 | funcG    |    37.38 μs |   357.33 μs |  3767.78 μs | 38112.20 μs | 
 | funcH    |    36.98 μs |   348.10 μs |  3569.84 μs | 38181.10 μs | 
 | funcI    |    32.27 μs |   354.47 μs |  3374.62 μs | 33140.90 μs | 

 - ## Internal Test Data Sorted
 |   name   |         10k |        100k |          1M |         10M
 | -------- | ----------- | ----------- | ----------- | ----------- | 
 | funcA    |    18.20 μs |   141.30 μs |  1297.18 μs | 10680.10 μs | 
 | funcB    |    15.11 μs |   135.41 μs |  1337.40 μs | 13223.60 μs | 
 | funcC    |    14.74 μs |    83.47 μs |  1320.96 μs | 12235.90 μs | 
 | funcD    |    17.57 μs |   130.21 μs |  1204.38 μs | 11526.30 μs | 
 | funcE    |    18.73 μs |   132.22 μs |  1185.90 μs | 12151.40 μs | 
 | funcF    |    16.56 μs |    84.88 μs |   703.78 μs |  7620.40 μs | 
 | funcG    |    18.90 μs |   129.85 μs |  1217.08 μs | 12104.30 μs | 
 | funcH    |    18.05 μs |   128.93 μs |  1197.54 μs | 11843.80 μs | 
 | funcI    |    33.54 μs |   334.07 μs |  3156.36 μs | 30824.00 μs | 

 - ## Input Files
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     1.00 μs |    10.00 μs |   926.00 μs | 
 | funcB    |     1.00 μs |    21.00 μs |  2150.00 μs | 
 | funcC    |     1.00 μs |    13.00 μs |  1297.00 μs | 
 | funcD    |     1.00 μs |    17.00 μs |  1724.00 μs | 
 | funcE    |        0 μs |    33.00 μs |  3764.00 μs | 
 | funcF    |     1.00 μs |    34.00 μs |  3728.00 μs | 
 | funcG    |        0 μs |    33.00 μs |  3729.00 μs | 
 | funcH    |        0 μs |    33.00 μs |  3796.00 μs | 
 | funcI    |        0 μs |    30.00 μs |  3576.00 μs | 

 - ## Input Files Sorted
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     1.00 μs |    18.00 μs |  1043.00 μs | 
 | funcB    |     1.00 μs |    14.00 μs |  1369.00 μs | 
 | funcC    |     1.00 μs |    14.00 μs |  1530.00 μs | 
 | funcD    |     1.00 μs |    17.00 μs |  1175.00 μs | 
 | funcE    |     1.00 μs |    18.00 μs |  1292.00 μs | 
 | funcF    |     1.00 μs |    14.00 μs |   813.00 μs | 
 | funcG    |        0 μs |    15.00 μs |  1293.00 μs | 
 | funcH    |        0 μs |    12.00 μs |  1210.00 μs | 
 | funcI    |        0 μs |    46.00 μs |  2925.00 μs | 

 - ## Input Files - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     0.03 μs |     9.78 μs |  1016.23 μs | 
 | funcB    |     0.02 μs |    14.73 μs |  2260.43 μs | 
 | funcC    |     0.08 μs |    13.63 μs |  1330.34 μs | 
 | funcD    |        0 μs |    17.33 μs |  1806.30 μs | 
 | funcE    |     0.02 μs |    37.24 μs |  3794.88 μs | 
 | funcF    |     0.01 μs |    37.78 μs |  3649.64 μs | 
 | funcG    |        0 μs |    37.60 μs |  3791.37 μs | 
 | funcH    |     0.01 μs |    37.74 μs |  3770.87 μs | 
 | funcI    |     0.14 μs |    34.15 μs |  3389.01 μs | 

 - ## Input Files Sorted - Iterated 100x
 |   name   | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt
 | -------- | ----------- | ----------- | ----------- | 
 | funcA    |     0.01 μs |    17.18 μs |   992.51 μs | 
 | funcB    |     0.01 μs |    14.94 μs |  1265.23 μs | 
 | funcC    |     0.05 μs |    14.31 μs |  1329.79 μs | 
 | funcD    |        0 μs |    11.85 μs |  1212.94 μs | 
 | funcE    |     0.01 μs |    13.49 μs |  1244.42 μs | 
 | funcF    |     0.01 μs |     8.21 μs |   700.33 μs | 
 | funcG    |        0 μs |    12.83 μs |  1199.52 μs | 
 | funcH    |     0.44 μs |    13.45 μs |  1146.55 μs | 
 | funcI    |        0 μs |    35.68 μs |  3168.15 μs | 
 ### --- End ---
