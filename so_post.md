I provided different version of test functions with incremental code optimization changes to check whether those changes really improved the execution time. Surprised me... it is not always the case! It depends a lot on how the numbers are arranged in the list.

[Here](https://github.com/esraels/so2025_challenge6?tab=readme-ov-file#the-result) is my git repo to see the full code, test scripts, and more results.

- The test functions are below:

```c++
/* ===================================
 * funcA: Count and search with maxCount
--------------------------------------*/
void funcA(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMaxCount = 0, vMaxCount = 0; 
    // --- count
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto vCur = ++counts[ listN[i] ];
        if(vMaxCount < vCur) {
            vMaxCount = vCur;
            iMaxCount = listN[i];
        }
    }
    // --- search and get the results
    const size_t numCounts = counts.size();
    for(size_t i = 0; i < numCounts; i++){
        if ( counts[i] != vMaxCount ) continue;
        results.push_back(i);
    }
    
}

/* ===================================
 * funcB: Count and search maxcount from index iMin.
--------------------------------------*/
void funcB(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    
    int iMin = 0, vMaxCount = 0;  //
    // --- count
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        auto const vCur = ++counts[ iCur ];
        if(vMaxCount < vCur) {
            vMaxCount = vCur;
            iMin = iCur;
        } else if (vMaxCount == vCur && iCur < iMin) {
            iMin = iCur;
        }
    }
    // --- search and get the results
    const size_t numCounts = counts.size();
    for(size_t i = iMin; i < numCounts; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }
    
}


/* ===================================
 * funcC: Count and search maxcount from iMin to iMax indices
 -------------------------------------*/
void funcC(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0, vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        auto const vCur = ++counts[ iCur ];
        if(vMaxCount < vCur) {
            vMaxCount = vCur;
            iMin = iMax = iCur;
        } else if (vMaxCount == vCur) {
            if (iCur < iMin) {
                iMin = iCur;
            }
            else if (iCur > iMax) {
                iMax = iCur;
            }
        }
    }
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }
    
}

/* ===================================
 * funcD: Count and search maxcount from iMin to iMax indices
 *  + take advantage of consecutive same numbers.
 -------------------------------------*/
void funcD(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0, vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        
        // --- count ahead consecutive same numbers
        int j = i+1;
        while (iCur == listN[j] && j < numItems) j++;
        auto const vCur = counts[ iCur ] += (j - i);
        i = j - 1;

        // --- update searching info
        if(vMaxCount < vCur) {
            vMaxCount = vCur;
            iMin = iMax = iCur;
        } else if (vMaxCount == vCur) {
            if (iCur < iMin) {
                iMin = iCur;
            }
            else if (iCur > iMax) {
                iMax = iCur;
            }
        }
    }
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }
    
}

/* ===================================
 * funcE: Count and search maxcount from iMin to iMax indices
 *  + take advantage of consecutive same numbers
 *  + less branches inside the loop by using &,| instead of &&,||
 *     to lessen branch mispredictions.
 -------------------------------------*/
void funcE(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0;
    int vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        
        // --- count ahead consecutive same numbers
        int j = i+1;
        while (iCur == listN[j] & j < numItems) j++;
        auto const vCur = counts[ iCur ] += (j - i);
        i = j - 1;

        // --- update searching info
        const int diffCount = vCur - vMaxCount;
        const int diffIdxMin = iCur - iMin;
        const int diffIdxMax = iCur - iMax;
        const bool bDiffCountNeg = diffCount < 0;
        const bool bDiffCount0   = diffCount == 0;
        vMaxCount += ((diffCount <= 0)-1) & diffCount;
        iMin += ((bDiffCountNeg | (bDiffCount0 & diffIdxMin >= 0))-1) & diffIdxMin;
        iMax += ((bDiffCountNeg | (bDiffCount0 & diffIdxMax <= 0))-1) & diffIdxMax;

    }
    
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }
    
}

/* ===================================
 * funcF: Count and search maxcount from iMin to iMax indices
 *  + take advantage of consecutive same numbers
 *  ? convert back branches(&&,||) on conditions expression
 *    because surprisingly, it is sometimes faster than funcE
 *    (I'm still not sure why.)
 -------------------------------------*/
void funcF(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0;
    int vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        
        // --- count ahead consecutive same numbers
        int j = i+1;
        while (iCur == listN[j] && j < numItems) j++;   // changed back from & to &&.
        auto const vCur = counts[ iCur ] += (j - i);
        i = j - 1;

        // --- update searching info
        const int diffCount = vCur - vMaxCount;
        const int diffIdxMin = iCur - iMin;
        const int diffIdxMax = iCur - iMax;
        const bool bDiffCountNeg = diffCount < 0;
        const bool bDiffCount0   = diffCount == 0;
        vMaxCount += ((diffCount <= 0)-1) & diffCount;
        iMin += ((bDiffCountNeg || (bDiffCount0 && diffIdxMin >= 0))-1) & diffIdxMin;  //changed back from &,| to &&,||
        iMax += ((bDiffCountNeg || (bDiffCount0 && diffIdxMax <= 0))-1) & diffIdxMax;

    }
    
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }

}

/* ===================================
 * funcG: Count and search maxcount from iMin to iMax indices
 *  + take advantage of consecutive same numbers
 *  + less branches inside the loop by using &,| instead of &&,||
 *     to lessen branch mispredictions.
 *  ? remove 'const' variables inside the loop.
 -------------------------------------*/
void funcG(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0;
    int vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto iCur = listN[i];
        
        // --- count ahead consecutive same numbers
        int j = i+1;
        while (iCur == listN[j] & j < numItems) j++;
        auto vCur = counts[ iCur ] += (j - i);
        i = j - 1;

        // --- update searching info
        int diffCount = vCur - vMaxCount;
        int diffIdxMin = iCur - iMin;
        int diffIdxMax = iCur - iMax;
        bool bDiffCountNeg = diffCount < 0;
        bool bDiffCount0   = diffCount == 0;
        vMaxCount += ((diffCount <= 0)-1) & diffCount;
        iMin += ((bDiffCountNeg | (bDiffCount0 & diffIdxMin >= 0))-1) & diffIdxMin;
        iMax += ((bDiffCountNeg | (bDiffCount0 & diffIdxMax <= 0))-1) & diffIdxMax;

    }
    
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }

}

/* ===================================
 * funcH: Count and search maxcount from iMin to iMax indices
 *  + take advantage of consecutive same numbers
 *  + less branches inside the loop by using &,| instead of &&,||
 *     to lessen branch mispredictions.
 *  ? changed 'while' to 'for' for consecutive same numbers
 -------------------------------------*/
void funcH(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0;
    int vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto iCur = listN[i];
        
        // --- count ahead consecutive same numbers
        int j;
        for (j = i+1; iCur == listN[j] & j < numItems; j++);
        auto vCur = counts[ iCur ] += (j - i);
        i = j - 1;

        // --- update searching info
        const int diffCount = vCur - vMaxCount;
        const int diffIdxMin = iCur - iMin;
        const int diffIdxMax = iCur - iMax;
        const bool bDiffCountNeg = diffCount < 0;
        const bool bDiffCount0   = diffCount == 0;
        vMaxCount += ((diffCount <= 0)-1) & diffCount;
        iMin += ((bDiffCountNeg | (bDiffCount0 & diffIdxMin >= 0))-1) & diffIdxMin;
        iMax += ((bDiffCountNeg | (bDiffCount0 & diffIdxMax <= 0))-1) & diffIdxMax;

    }
    
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }

}

/* ===================================
 * funcI: Count and search maxcount from iMin to iMax indices
 *  + less branches inside the loop by using &,| instead of &&,||
 *     to lessen branch mispredictions.
 -------------------------------------*/
void funcI(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0;
    int vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        auto const vCur = ++counts[ iCur ];

        // --- update searching info
        const int diffCount = vCur - vMaxCount;
        const int diffIdxMin = iCur - iMin;
        const int diffIdxMax = iCur - iMax;
        const bool bDiffCountNeg = diffCount < 0;
        const bool bDiffCount0   = diffCount == 0;
        vMaxCount += ((diffCount <= 0)-1) & diffCount;
        iMin += ((bDiffCountNeg | (bDiffCount0 & diffIdxMin >= 0))-1) & diffIdxMin;
        iMax += ((bDiffCountNeg | (bDiffCount0 & diffIdxMax <= 0))-1) & diffIdxMax;

    }
    
    // --- search and get the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }
    
}
```

In summary, these are the functions with their descriptions:

| name | Description |
|:--- |:--- |
| funcA | unoptimized. basis for correct results. |
| funcB | like funcA but search maxcount starting from iMin. |
| funcC | like funcB but now, search upto iMax only. |
| funcD | like funcC but counting ahead consecutive same numbers. |
| funcE | like funcD but converted most conditional branches to branchless version. |
| funcF | like funcE but converted back the branches that uses `&&`, and \` |
| funcG | like funcE but remove all `const` specifier of vars inside the loops. |
| funcH | like funcE but changed the inside loop from `while` to `for`. |
| funcI | like funcE but removed counting ahead of consecutive same numbers. |

## The Result:

- Below is a sample generated result of this app.
- You can see that the optimize version of functions is slower than the unoptimized version when the input data is purely random.
- When the data are sorted, better performance is achieved.
- In my conclusion, it really pays well if the input data is normalized before processing. In this case, "sorted".
- For the unoptimized version, the execution time is consistent whether the data is sorted or not.

# Benchmark Results: Built with `-std=c++17 -O3`

- ## Internal Test Data

| name | 10k | 100k | 1M | 10M |
|:--- | ---:| ---:| ---:| ---:|
| funcA | 5.84 μs | 57.12 μs | 578.34 μs | 6522.20 μs |
| funcB | 21.85 μs | 220.06 μs | 2104.02 μs | 20774.20 μs |
| funcC | 5.49 μs | 57.69 μs | 540.14 μs | 5554.10 μs |
| funcD | 12.25 μs | 119.10 μs | 1192.10 μs | 11800.10 μs |
| funcE | 21.36 μs | 218.82 μs | 2199.56 μs | 21898.20 μs |
| funcF | 14.31 μs | 142.08 μs | 1419.20 μs | 14195.70 μs |
| funcG | 21.49 μs | 218.27 μs | 2189.46 μs | 21813.90 μs |
| funcH | 21.23 μs | 218.92 μs | 2188.74 μs | 21745.00 μs |
| funcI | 20.74 μs | 211.34 μs | 2118.92 μs | 21211.40 μs |

- ## Internal Test Data Sorted

| name | 10k | 100k | 1M | 10M |
|:--- | ---:| ---:| ---:| ---:|
| funcA | 16.27 μs | 64.75 μs | 479.82 μs | 4727.50 μs |
| funcB | 9.12 μs | 81.17 μs | 698.62 μs | 6906.10 μs |
| funcC | 10.07 μs | 62.45 μs | 478.00 μs | 4788.50 μs |
| funcD | 10.06 μs | 41.42 μs | 361.02 μs | 3613.00 μs |
| funcE | 11.07 μs | 52.21 μs | 474.64 μs | 4758.40 μs |
| funcF | 10.02 μs | 41.75 μs | 362.26 μs | 3648.90 μs |
| funcG | 11.29 μs | 51.46 μs | 470.04 μs | 4729.90 μs |
| funcH | 11.00 μs | 53.18 μs | 472.74 μs | 4712.20 μs |
| funcI | 22.21 μs | 221.65 μs | 2059.62 μs | 20615.30 μs |

- ## Input Files

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 0 μs | 6.00 μs | 571.00 μs |
| funcB | 0 μs | 15.00 μs | 1467.00 μs |
| funcC | 0 μs | 6.00 μs | 516.00 μs |
| funcD | 0 μs | 12.00 μs | 1151.00 μs |
| funcE | 0 μs | 21.00 μs | 2135.00 μs |
| funcF | 0 μs | 14.00 μs | 1379.00 μs |
| funcG | 0 μs | 21.00 μs | 2123.00 μs |
| funcH | 0 μs | 21.00 μs | 2161.00 μs |
| funcI | 0 μs | 20.00 μs | 2063.00 μs |

- ## Input Files Sorted

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 0 μs | 16.00 μs | 487.00 μs |
| funcB | 0 μs | 9.00 μs | 699.00 μs |
| funcC | 0 μs | 10.00 μs | 489.00 μs |
| funcD | 0 μs | 10.00 μs | 352.00 μs |
| funcE | 0 μs | 11.00 μs | 456.00 μs |
| funcF | 0 μs | 10.00 μs | 345.00 μs |
| funcG | 0 μs | 8.00 μs | 468.00 μs |
| funcH | 0 μs | 6.00 μs | 465.00 μs |
| funcI | 0 μs | 22.00 μs | 2091.00 μs |

- ## Input Files - Run 100x Each

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 0.01 μs | 5.12 μs | 553.54 μs |
| funcB | 0 μs | 8.72 μs | 1406.53 μs |
| funcC | 0 μs | 6.85 μs | 542.77 μs |
| funcD | 0 μs | 11.81 μs | 1159.99 μs |
| funcE | 0 μs | 21.05 μs | 2121.98 μs |
| funcF | 0 μs | 14.16 μs | 1375.58 μs |
| funcG | 0 μs | 21.02 μs | 2138.88 μs |
| funcH | 0 μs | 21.30 μs | 2134.64 μs |
| funcI | 0 μs | 20.05 μs | 2084.02 μs |

- ## Input Files Sorted - Run 100x Each

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 0.01 μs | 14.97 μs | 474.40 μs |
| funcB | 0 μs | 9.15 μs | 697.87 μs |
| funcC | 0 μs | 10.00 μs | 469.82 μs |
| funcD | 0 μs | 4.13 μs | 346.24 μs |
| funcE | 0 μs | 5.10 μs | 458.06 μs |
| funcF | 0 μs | 4.09 μs | 346.53 μs |
| funcG | 0 μs | 5.15 μs | 458.65 μs |
| funcH | 0 μs | 5.00 μs | 462.79 μs |
| funcI | 0 μs | 22.10 μs | 2077.07 μs |

## Learnings:

- I improved my skills in boolean algebra to optimize the conditional expressions.
- I discovered how to convert code branches to their branchless version.
- I realized, I really should benchmark my work when I need to optimize. It's not enough to know that you added an optimization code.
- To really achieve better performance, you need to normalize the data. (in this case, *SORT* them). Feeding a random data to an optimized function does not guarantee the optimization will take effect. Sometimes the result will be worse than the unoptimized version. The optimization must be applied to both the code and the data, not just to the code.
- Using a documentation syntax, like `markdown`, for the logs will make the result more presentable and easier to see and analyze.

## Conclusion:

- Optimize both the data and the code to achieve better performance.