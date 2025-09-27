#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <string>

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

void clearCounts(vector<int>& counts) {
    std::fill(counts.begin(), counts.end(), 0);
}

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

/* ===================================
 * funcA: Count and search
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
 * funcB: Count and search from index iMax.
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
 * funcC: Count and search from iMin to iMax indices
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
 * funcD: Count and search from iMin to iMax indices
 *  + take advantage of consecutive same numbers.
 -------------------------------------*/
void funcD(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0, vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        
        // --- skip the same numbers
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
 * funcE: Count and search from iMin to iMax indices
 *  + take advantage of consecutive same numbers
 *  + convert to lesser branch mispredictions.
 -------------------------------------*/
void funcE(const vector<int>& listN, vector<int>& counts, vector<int>& results){
    int iMin = 0, iMax = 0, vMaxCount = 0;
    const size_t numItems = listN.size();
    for(size_t i = 0; i < numItems; i++){
        auto const iCur = listN[i];
        
        // --- count ahead the same numbers
        int j = i+1;
        while ((iCur == listN[j]) & (j < numItems)) j++;
        auto const vCur = counts[ iCur ] += (j - i);
        i = j - 1;

        // --- update searching info
        const int diffCount = vCur - vMaxCount;
        const int diffIdxMin = iCur - iMin;
        const int diffIdxMax = iCur - iMax;
        const bool bCountsNotEq = (diffCount != 0);

        vMaxCount += ((diffCount < 0)-1) & diffCount;
        iMin += ((bCountsNotEq | (diffIdxMin >= 0))-1) & diffIdxMin;
        iMax += ((bCountsNotEq | (diffIdxMax <= 0))-1) & diffIdxMax;

    }
    // --- search and print the results
    for(size_t i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        results.push_back(i);
    }
    
}

using func_t = void(*)(const vector<int>&, vector<int>&, vector<int>&);


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

int main(){

    //smallTest();

    //return 0;

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
    };

    //TODO: generate own list of random numbers.
    vector<vector<int>> list10k(100, vector<int>(10'000, 0));
    vector<vector<int>> list100k(100, vector<int>(100'000, 0));
    vector<vector<int>> list1M(5, vector<int>(1'000'000, 0));

    auto randomPure = [](auto& listN) {
        for(auto& list : listN) {
            for(auto& v : list) {
                v = rand() % 1000;
            }
        }
    };

    decltype(Timer().getElapsed()) dur;

    vector<vector<vector<int>>*> listTests = { &list10k, &list100k, &list1M };
    struct testInfo {
        const char* name;
        vector<vector<int>>* listTest;
        vector<Timer::duration_t> listDurations;
    } listTestInfo[] = {
        {"10k", &list10k},
        {"100k", &list100k},
        {"1M",  &list1M},
    };

    for(auto& test : listTestInfo){
        randomPure(*test.listTest);
        for(auto& f : listFuncToTest) {
            Timer::duration_t totalDur = 0;
            cout << "\n --- Testing " << f.name << " with " << test.name << " ---" << endl;
            for(auto& listNums : *test.listTest) {
                //if(totalDur = -1) continue;  // skip test if prev result(s) was unmatched.

                // --- prepare input/output containers.
                std::fill(counts.begin(), counts.end(), 0); 
                results.clear();

                // --- execute process
                timer.start();
                f.func(listNums, counts, results);
                timer.stop();

                // --- accumulate execution time.
                totalDur += timer.getElapsed();

                // --- check if correct result.
                if(f.func == funcA) {
                    expected = results;
                } else if(expected != results) {
                    totalDur = -1;
                    cout << "unmatched result occurred!" << endl;
                    cout << "expected: count(" << expected.size() << ") " << endl; 
                    for (int i = 0; i < 5 && i < expected.size(); i++) {
                        cout << expected[i] << " ";
                        cout << (expected.size() > 5 ? "..." : "") << endl;
                    }
                    cout << "result: count(" << results.size() << ") " << endl; 
                    for (int i = 0; i < 5 && i < results.size(); i++) {
                        cout << results[i] << " ";
                        cout << (results.size() > 5 ? "..." : "") << endl;
                    }
                    break;
                }
            }
            cout << "total duration: " << totalDur << " ms" << endl;
            test.listDurations.push_back(totalDur);
            
        }
    }

    // --- print results column labels
    cout << "\n\n | name "; 
    for(auto& t : listTestInfo) cout << "| " << t.name ;  
    cout << endl;
    cout << " | --- | --- | --- | --- |" << endl;
        // --- print func names and durations
        //for(auto& f : listFuncToTest){
        for (int f = 0; f < sizeof(listFuncToTest) / sizeof(listFuncToTest[0]); f++)
    {
        auto& func = listFuncToTest[f];
        
        cout << " | " << func.name << " | ";
        for(auto& test : listTestInfo) {
            auto dur = test.listDurations[f];
            cout << test.listDurations[f] << " us | ";
        }
        cout << endl;
    }

    cout << "\n--- finished! ---" << endl;

    return 0;
}
