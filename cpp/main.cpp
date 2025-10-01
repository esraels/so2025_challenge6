#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

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
    string name;
    vector<vector<int>> listTest;
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

void printSummaryTable(const vector<SFuncToTest>& listFuncToTest, const vector<STestData>& listTestData, int numIter = 1, bool bShowDesc = false){
    // --- column labels ---
    cout << " |   name  "; 
    for(auto& t : listTestData) 
        cout << " | " << std::setw(11) << t.name ;  
    if (bShowDesc) cout << " | Description ";
    cout << endl;
    
    // --- divider line ---
    cout << " | --------";
    for(int i=0; i < listTestData.size(); i++) 
        cout << " | -----------"; 
    if(bShowDesc) cout << " | ---------------------------------";
    cout << " | " << endl;

    // --- rows ---
    cout << setprecision(2) << fixed;
    for (int f = 0; f < listFuncToTest.size(); f++) {
        auto& func = listFuncToTest[f];
        cout << " | " << func.name << "    | ";
        for(auto& test : listTestData) {
            if(test.listDurations[f] > 0){
                auto avgDur = double(test.listDurations[f]) / double(test.listTest.size() * numIter);
                cout << std::setw(8) << avgDur << " μs | ";
            } else {
                cout << std::setw(8) << test.listDurations[f] << " μs | ";
            }
        }
        if (bShowDesc) cout << " " << func.sDescription;
        cout << endl;
    }
} //printSummaryTable()...

void printHelp(string sAppName){
    cout << 
    "\nUsage: '" << sAppName << "' [OPTIONS]... [FILES]..."
    "\n[FILES]: One or more text files that should contain list of numbers "
    "\n       separated by newlines. Wildcards and globing are not supported."
    "\nOPTIONS: "
    "\n   -s, --sort-data            sort the test data before testing."
    "\n   -n, --num-iterations NUM   each test data will be feed to each"
    "\n                              test functions NUM times for better"
    "\n                              execution time measurement."
    "\n   -d, --describe-funcs       show description of internal test data"
    "\n                              in summary table."
    "\n   -t, --table-only           print the summary table only. no-verbose."
    "\n       --no-verbose           same as --table-only."
    "\n   -h, -?, --help             print this help document."
    "\n"
    "\nIf there are no valid input files provided, the app will generate its"
    "\nown internal test data. The --num-iteration value won't take effect."
    "\n";
}

void ErrorExit(int errCode, const string& errMsg){
    cerr << "ERROR: "<< errMsg << endl;
    cerr << "Try '-?' for help." << endl;
    exit(errCode);
}

vector<int> getListNumsFromFile(ifstream& file) {
    vector<int> listNums;
    string line;
    while (std::getline(file, line)){
        int num = 0;
        stringstream(line) >> num;
        listNums.push_back(num) ;
    }
    return listNums;
}

int main(int argc, char* argv[]){

    // --- input functions
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

    // --- input test data
    vector<STestData> listTestData;

    // --- process arguments...
    bool bSortedData = false;
    bool bShowFuncDesc = false;
    bool bVerbose = true;
    int numIterations = 1;

    // --- look first for verbosity options
    for(int i = 1; i < argc; i++){
        auto sArg = string(argv[i]);
        if (sArg.empty()) continue;
        else if (sArg == "-t" || sArg == "--table-only" || sArg == "no-verbose") {
            bVerbose = false;
            break;
        }
    }

    // verbose logger
    auto vLog = [&](const string& logMsg) {
        if(!bVerbose) return;
        cout << logMsg << endl;
    };

    vLog("- Processing Arguments...");

    for(int i = 1; i < argc; i++){
        auto sArg = string(argv[i]);
        if (sArg.empty()) continue;
        else if (sArg == "-s" || sArg == "--sort-data") bSortedData = true;
        else if (sArg == "-d" || sArg == "--describe-funcs") bShowFuncDesc = true;
        else if (sArg == "-t" || sArg == "--table-only" || sArg == "no-verbose") {
            bVerbose = false;
        }
        else if (sArg == "-h" || sArg == "--help" || sArg == "-?") {
            printHelp(argv[0]);
            exit(0);
        } 
        else if (sArg == "-n" || sArg == "--num-iterations") {
            int parsedNum = -1;
            if(i < argc-1) {
                stringstream sNum(argv[i+1]);
                sNum >> parsedNum;
            }
            if (parsedNum > 0){
                numIterations = parsedNum;
            } else {
                ErrorExit(1, "invalid value for option: -n, --num-iterations.");
            }
        }
        else if (sArg[0] != '-' ){
            ifstream file(sArg);
            if(file.is_open()){
                if(bVerbose) cout << "- Parsing '" << sArg << "' file..." << endl;
                vector<int> listNums = getListNumsFromFile(file);
                if(!listNums.empty()){
                    STestData data;
                    data.listTest.push_back(std::move(listNums));
                    data.name = sArg;
                    listTestData.push_back(std::move(data));
                } else {
                    if (bVerbose) cout << "   - '" << sArg << "' file has empty valid numbers." << endl;
                }
            } else {
                ErrorExit(2, "Failed to open file: '" + sArg + "'");
            }
            file.close();
        }
        else {
            ErrorExit(3, "Invalid argument option: '" + sArg + "'");
        }
    }

    // --- list of internal test data generators.
    // note: only randomPure() is used for now.
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
    auto randomMultipleAnswers = [](auto& listN) {
        // todo: implement
    };
    auto randomMultipleAnswersWithinControlledRange = [](auto& listN) {
        // todo: implement
    };

    // --- if input data from command line argument is empty...
    if (listTestData.empty()){
        vector<STestData> internalTestData {
            {"10k", vector(100, vector<int>(10'000))},
            {"100k", vector(100, vector<int>(100'000))},
            {"1M",  vector(50, vector<int>(1'000'000))},
            {"10M",  vector(10, vector<int>(10'000'000))},
        };

        // --- generate test data.
        vLog("- Generating internal test data...");
        for(auto& test : internalTestData){
            randomPure(test.listTest);
            //randomSorted(test.listTest);
        }
        listTestData = std::move(internalTestData);
        numIterations = 1;
    }
    
    // --- sorting test data.
    if(bSortedData) {
        vLog("- Sorting test data...");
        for(auto& listN : listTestData){
            for(auto& list : listN.listTest){
                sort(list.begin(), list.end());
            }
        }
    }

    // --- start benchmark
    vLog("# Start benchmarking...");
    Timer timer;
    vector<int> counts(1000, 0);
    vector<int> results(1000, 0);
    vector<int> expected;
    const int IDX_BASIS_FUNC = 0;

    for(auto& test : listTestData){
        //randomPure(*test.listTest);
        //randomSorted(*test.listTest);
        vector<vector<int>> listResult, listExpected;
        listExpected.clear();
        test.listDurations.clear();
        for(auto& f : listFuncToTest) {
            Timer::duration_t totalDur = 0;
            listResult.clear();
            if(bVerbose) {
                cout << "\n ## Testing `" << f.name << "` with `" << test.name << "`:" << endl;
                cout << "- dur list: " << endl << "    ```c++" << endl  << "    ";
            }
            for(int i = 0; i < numIterations; i++) {
                for(auto& listNums : test.listTest) {

                    // --- prepare input/output containers.
                    std::fill(counts.begin(), counts.end(), 0); 
                    results.clear();

                    // --- execute process
                    timer.start();
                    f.func(listNums, counts, results);
                    timer.stop();

                    // --- accumulate execution time.
                    if(bVerbose) cout << timer.getElapsed() << "μs, ";
                    totalDur += timer.getElapsed();
                    listResult.push_back(results);

                }
            }
            if(bVerbose) cout << endl << "    ```" << endl;
                   
            if (f.func == listFuncToTest[IDX_BASIS_FUNC].func) {
                listExpected = listResult;
                if(bVerbose) {
                    cout << "- get funcA result as basis." << endl;
                    cout << " - **actual result**: " << endl;
                    printResult(listResult);
                }
            } else if (listExpected != listResult) {
                totalDur = -1;
                if(bVerbose) {
                    cout << "- ### result not matched!" << endl;
                    printResultComparison(listExpected, listResult);
                }
                break;
            }

            test.listDurations.push_back(totalDur);

            if(bVerbose) {
                cout << "- ### total duration: " << totalDur << " μs" << endl;
                //cout << "### Result comparison:" << endl;
                //printResultComparison(listExpected, listResult);
            }

        }
    }

    // --- print average execution time summary table(in markdown syntax).
	vLog( "\n\n # Summary: Average execution time.");
    printSummaryTable(listFuncToTest, listTestData, numIterations, bShowFuncDesc);

    vLog("");

    return 0;
}
