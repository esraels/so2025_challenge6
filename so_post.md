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
- In my conclusion, it really pays well if the input data is normalized before processing. In this case, "sorted".
- For the unoptimized version, the execution time is consistent whether the data is sorted or not.

# Benchmark Results: Built with `-std=c++17 -O3`

- ## Internal Test Data

| name | 10k | 100k | 1M | 10M |
|:--- | ---:| ---:| ---:| ---:|
| funcA | 12.98 μs | 127.43 μs | 1294.88 μs | 13289.10 μs |
| funcB | 32.03 μs | 300.63 μs | 3072.36 μs | 29541.20 μs |
| funcC | 13.43 μs | 136.94 μs | 1367.16 μs | 13977.60 μs |
| funcD | 34.15 μs | 384.90 μs | 3215.48 μs | 32806.40 μs |
| funcE | 35.69 μs | 350.45 μs | 3721.40 μs | 36802.70 μs |
| funcF | 36.57 μs | 349.65 μs | 3336.06 μs | 36215.10 μs |
| funcG | 36.02 μs | 361.99 μs | 3763.10 μs | 37554.60 μs |
| funcH | 36.52 μs | 359.46 μs | 3644.96 μs | 36718.60 μs |
| funcI | 33.26 μs | 293.15 μs | 3238.12 μs | 34710.40 μs |

- ## Internal Test Data Sorted

| name | 10k | 100k | 1M | 10M |
|:--- | ---:| ---:| ---:| ---:|
| funcA | 19.71 μs | 155.93 μs | 1241.98 μs | 12754.20 μs |
| funcB | 18.79 μs | 187.89 μs | 1733.02 μs | 17893.50 μs |
| funcC | 15.03 μs | 147.79 μs | 1317.16 μs | 13302.60 μs |
| funcD | 16.06 μs | 75.89 μs | 695.16 μs | 7425.90 μs |
| funcE | 19.71 μs | 123.51 μs | 1170.90 μs | 12020.30 μs |
| funcF | 16.41 μs | 76.79 μs | 695.68 μs | 7230.10 μs |
| funcG | 19.39 μs | 123.29 μs | 1196.06 μs | 12149.20 μs |
| funcH | 19.99 μs | 123.35 μs | 1193.00 μs | 12297.80 μs |
| funcI | 36.60 μs | 337.31 μs | 3205.24 μs | 32053.20 μs |

- ## Input Files

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 1.00 μs | 12.00 μs | 1197.00 μs |
| funcB | 1.00 μs | 22.00 μs | 2271.00 μs |
| funcC | 0 μs | 13.00 μs | 1350.00 μs |
| funcD | 0 μs | 30.00 μs | 3199.00 μs |
| funcE | 0 μs | 33.00 μs | 3437.00 μs |
| funcF | 1.00 μs | 33.00 μs | 3536.00 μs |
| funcG | 0 μs | 32.00 μs | 3498.00 μs |
| funcH | 0 μs | 32.00 μs | 3620.00 μs |
| funcI | 0 μs | 30.00 μs | 3348.00 μs |

- ## Input Files Sorted

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 1.00 μs | 18.00 μs | 1249.00 μs |
| funcB | 1.00 μs | 18.00 μs | 1836.00 μs |
| funcC | 0 μs | 14.00 μs | 1417.00 μs |
| funcD | 0 μs | 14.00 μs | 799.00 μs |
| funcE | 1.00 μs | 18.00 μs | 1219.00 μs |
| funcF | 0 μs | 15.00 μs | 665.00 μs |
| funcG | 0 μs | 15.00 μs | 1168.00 μs |
| funcH | 0 μs | 12.00 μs | 1180.00 μs |
| funcI | 0 μs | 34.00 μs | 3159.00 μs |

- ## Input Files - Run 100x Each

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 0.01 μs | 12.23 μs | 1307.64 μs |
| funcB | 1.00 μs | 17.17 μs | 2412.52 μs |
| funcC | 0 μs | 13.30 μs | 1258.40 μs |
| funcD | 0 μs | 33.63 μs | 3271.69 μs |
| funcE | 0 μs | 36.18 μs | 3766.19 μs |
| funcF | 0.01 μs | 36.04 μs | 3613.89 μs |
| funcG | 0 μs | 35.21 μs | 3714.58 μs |
| funcH | 0.01 μs | 35.11 μs | 3757.49 μs |
| funcI | 0.42 μs | 32.77 μs | 3494.65 μs |

- ## Input Files Sorted - Run 100x Each

| name | input/100_nums.txt | input/10k_nums.txt | input/1M_nums.txt |
|:--- | ---:| ---:| ---:|
| funcA | 0.01 μs | 18.00 μs | 1122.91 μs |
| funcB | 1.00 μs | 17.97 μs | 1756.84 μs |
| funcC | 0 μs | 14.06 μs | 1324.73 μs |
| funcD | 0 μs | 8.84 μs | 678.32 μs |
| funcE | 0.01 μs | 12.52 μs | 1227.68 μs |
| funcF | 0.01 μs | 8.54 μs | 689.60 μs |
| funcG | 0 μs | 12.15 μs | 1221.19 μs |
| funcH | 0 μs | 13.05 μs | 1197.38 μs |
| funcI | 0 μs | 35.84 μs | 3203.73 μs |

## Learnings:

- I improved my skills in boolean algebra to optimize the conditional expressions.
- I discovered how to convert code branches to their branchless version.
- I realized, I really should benchmark my work when I need to optimize. It's not enough to know that you added an optimization code.
- To really achieve better performance, you need to normalize the data. (in this case, *SORT* them). Feeding a random data to an optimized function does not guarantee the optimization will take effect. Sometimes the result will be worse than the unoptimized version. The optimization must be applied to both the code and the data, not just to the code.
- Using a documentation syntax, like `markdown`, for the logs will make the result more presentable and easier to see and analyze.

## Conclusion:
- Optimize both the data and the code to achieve better performance.