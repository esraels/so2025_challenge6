#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

//int listN[] = {
vector<int> listNums {
    462,86,839,546,270,
    898,379,566,6,392,
    626,188,45,533,570,
    349,257,362,409,253,
    916,684,205,890,291,
    92,208,17,48,406,
    254,667,103,400,857,
    309,713,261,10,300,
    54,140,251,178,328,
    641,616,208,844,820,

    //208,
    //374, 374, 374,
    //100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
    //200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    
    //101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 
    //201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 

    832,658,290,188,663,
    180,105,996,351,429,
    374,780,179,585,343,
    752,756,193,518,90,
    641,482,546,694,936,
    357,799,878,733,805,
    287,843,189,374,168,
    430,785,396,707,694,
    439,262,657,892,905,
    871,863,873,488,653,
    
};

class Timer {
public:
    using time_t = std::chrono::high_resolution_clock::time_point;
    using duration_t = long long;
protected:
    time_t m_timeStart;
    duration_t m_timeElapsed;  //in milliseconds
public:
    Timer(): m_timeElapsed(0){}
    ~Timer(){}
    void start() {
        m_timeStart = std::chrono::high_resolution_clock::now();
    }
    void stop() {
        auto timeEnd = std::chrono::high_resolution_clock::now();
        m_timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - m_timeStart).count();
    }
    auto getElapsed() {
        return m_timeElapsed;
    }
    void printElapsed() {
        cout << m_timeElapsed << " ms";
    }
};

using func_t = void(*)(const vector<int>&, vector<int>&, vector<int>&);

struct STestData {
    const char* name;
    vector<vector<int>>* listTest;
    vector<Timer::duration_t> listDurations;
};

struct SFuncToTest {
    const char* name;
    func_t func;
    const char* sDescription;
};

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

void smallTest() {

    Timer timer;
    vector<int> counts(1000, 0);
    vector<int> results(1000, 0);
    vector<int> expected;

    struct {
        const char* name;
        func_t func;
    } listFuncToTest[] = {
        {"funcA", funcA},
        {"funcB", funcB},
        {"funcC", funcC},
        {"funcD", funcD},
        {"funcE", funcE},
        {"funcF", funcF},
        {"funcG", funcG},
    };

    // --- test candidate functions
    for(auto& f : listFuncToTest) {
        
        // --- prepare input/output containers.
        std::fill(counts.begin(), counts.end(), 0); 
        results.clear();

        // --- execute process
        timer.start();
        f.func(listNums, counts, results);
        timer.stop();

        // --- print results
        cout << "---" << f.name << ": Result ---" << endl;
        cout << "duration: " << timer.getElapsed() << " ms" << endl;
        cout << "result count: " << results.size() << endl;
        cout << "result numbers: "; for(auto v : results) { cout << v << " "; }; cout << endl;

        if(f.func == funcA) {
            expected = results;
        } else {
            cout << "result matched: " << (expected == results ? "true" : "false") << endl;
        }
        
        cout << "\n\n";
        
    }

    cout << "\n--- finished! ---" << endl;
}

void printResult(const vector<vector<int>>& listResult){
    cout << "    ```c++" << endl << "    ";
    for(auto listNums : listResult) {
        cout << "("; for(auto v : listNums) { cout << v << " "; }; cout << "), ";
    }
    cout << endl << "    ```" << endl;
}

void printResultComparison(const vector<vector<int>>& listExpected, const vector<vector<int>>& listResult) {
    
    cout << " - **expected result**: " << endl;
    printResult(listExpected);

    cout << " - **actual result**: " << endl;
    printResult(listResult);

}

void printSummaryTable(const vector<SFuncToTest>& listFuncToTest, const vector<STestData>& listTestData){
        // --- title ---
    cout << "\n\n # Summary: Average execution time." << endl;
    
    // --- column labels ---
    cout << "\n\n |   name  "; 
    for(auto& t : listTestData) 
        cout << " | " << std::setw(11) << t.name ;  
    cout << " | Description " << endl;
    
    // --- divider line ---
    cout << " | --------";
    for(int i=0; i < listTestData.size(); i++) 
        cout << " | -----------"; 
    cout << " | --------------------------------- |" << endl;

    // --- rows ---
    cout << setprecision(2) << fixed;
    for (int f = 0; f < listFuncToTest.size(); f++) {
        auto& func = listFuncToTest[f];
        cout << " | " << func.name << "    | ";
        for(auto& test : listTestData) {
            if(test.listDurations[f] > 0){
                auto avgDur = double(test.listDurations[f]) / double(test.listTest->size());
                cout << std::setw(8) << avgDur << " μs | ";
            } else {
                cout << test.listDurations[f] << " μs | ";
            }
        }
        cout << " " << func.sDescription;
        cout << endl;
    }
} //printSummaryTable()...

int main(){

    //smallTest();

    //return 0;

    const int IDX_BASIS_FUNC = 0;

    Timer timer;
    vector<int> counts(1000, 0);
    vector<int> results(1000, 0);
    vector<int> expected;


    vector<SFuncToTest> listFuncToTest = {
        {"funcA", funcA, "unoptimized. basis for correct results." },
        {"funcB", funcB, "like funcA but search maxcount starting from iMin." },
        {"funcC", funcC, "like funcB but now, search upto iMax only." },
        {"funcD", funcD, "like funcC but counting ahead consecutive same numbers." },
        {"funcE", funcE, "like funcD but converted most conditional branches to branchless version." },
        {"funcF", funcF, "like funcE but converted back the branches that uses `&&`, and `||`." },
        {"funcG", funcG, "like funcE but remove all `const` specifier of vars inside the loops." },
        {"funcH", funcH, "like funcE but changed the inside loop from `while` to `for`.		" },
    };

    //TODO: generate own list of random numbers.
    vector<vector<int>> list10k(100, vector<int>(10'000, 0));
    vector<vector<int>> list100k(100, vector<int>(100'000, 0));
    vector<vector<int>> list1M(100, vector<int>(1'000'000, 0));
    vector<vector<int>> list10M(10, vector<int>(10'000'000, 0));

    srand(time(0));
    auto randomPure = [](auto& listN) {
        for(auto& list : listN) {
            for(auto& v : list) {
                v = rand() % 1000;
            }
        }
    };
    auto randomSorted = [](auto& listN) {
        for(auto& list : listN) {
            for(auto& v : list) {
                v = rand() % 1000;
            }
            sort(list.begin(), list.end());
        }
    };

    vector<STestData> listTestData = {
        {"10k", &list10k},
        {"100k", &list100k},
        {"1M",  &list1M},
        {"10M",  &list10M},
    };

    for(auto& test : listTestData){
        //randomPure(*test.listTest);
        randomSorted(*test.listTest);
        vector<vector<int>> listResult, listExpected;
        listExpected.clear();
        test.listDurations.clear();
        for(auto& f : listFuncToTest) {
            Timer::duration_t totalDur = 0;
            listResult.clear();
            cout << "\n ## Testing `" << f.name << "` with `" << test.name << "`:" << endl;
            cout << "- dur list: " << endl << "    ```c++" << endl  << "    ";
            for(auto& listNums : *test.listTest) {

                // --- prepare input/output containers.
                std::fill(counts.begin(), counts.end(), 0); 
                results.clear();

                // --- execute process
                timer.start();
                f.func(listNums, counts, results);
                timer.stop();

                // --- accumulate execution time.
                cout << timer.getElapsed() << "μs, ";
                totalDur += timer.getElapsed();
                listResult.push_back(results);

            }
            cout << endl << "    ```" << endl;
                   
            if (f.func == listFuncToTest[IDX_BASIS_FUNC].func) {
                listExpected = listResult;
                cout << "- get funcA result as basis." << endl;
                cout << " - **actual result**: " << endl;
                printResult(listResult);
            } else if (listExpected != listResult) {
                totalDur = -1;
                cout << "- ### result not matched!" << endl;
                printResultComparison(listExpected, listResult);
                break;
            }

            cout << "- ### total duration: " << totalDur << " μs" << endl;
            test.listDurations.push_back(totalDur);

            //cout << "### Result comparison:" << endl;
            //printResultComparison(listExpected, listResult);

        }
    }

    // --- print average execution time summary table(in markdown syntax).
    printSummaryTable(listFuncToTest, listTestData);

    cout << endl;

    return 0;
}
