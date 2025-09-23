#include <iostream>
#include <chrono>

using namespace std;

int listN[] = {
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

int counts[1000] = {0};

void clearCounts() {
    for(int i = 0; i < sizeof(counts)/sizeof(*counts); i++){
        counts[i] = 0;
    }
}

class Timer {
    using time_t = std::chrono::high_resolution_clock::time_point;
protected:
    time_t m_timeStart;
    long long m_timeElapsed;  //in milliseconds
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
        cout << m_timeElapsed << " ms" << std::endl;
    }
};

/* ===================================
 * funcA: Count and search
--------------------------------------*/
void funcA(){
    clearCounts();
    int iMaxCount = 0, vMaxCount = 0; 
    // --- count
    for(int i = 0; i < sizeof(listN)/sizeof(*listN); i++){
        auto vCur = ++counts[ listN[i] ];
        if(vMaxCount < vCur) {
            vMaxCount = vCur;
            iMaxCount = listN[i];
        }
    }
    cout << "Appearance Count: " << vMaxCount << endl;
    cout << "Numbers:" << endl;
    // --- search and print the results
    for(int i = 0; i < sizeof(counts)/sizeof(*counts); i++){
        if ( counts[i] != vMaxCount ) continue;
        cout << "" << i << ", ";
    }
}

/* ===================================
 * funcB: Count and search from index iMax.
--------------------------------------*/
void funcB(){
    clearCounts();
    int iMin = 0, vMaxCount = 0;  //
    // --- count
    for(int i = 0; i < sizeof(listN)/sizeof(*listN); i++){
        auto const iCur = listN[i];
        auto const vCur = ++counts[ iCur ];
        if(vMaxCount < vCur) {
            vMaxCount = vCur;
            iMin = iCur;
        } else if (vMaxCount == vCur && iCur < iMin) {
            iMin = iCur;
        }
    }
    cout << "Appearance Count: " << vMaxCount << endl;
    cout << "Numbers:" << endl;
    // --- search and print the results
    for(int i = iMin; i < sizeof(counts)/sizeof(*counts); i++){
        if (counts[i] != vMaxCount) continue;
        cout << "" << i << ", ";
    }
}


/* ===================================
 * funcC: Count and search from iMin to iMax indices
 -------------------------------------*/
void funcC(){
    clearCounts();
    int iMin = 0, iMax = 0, vMaxCount = 0;
    for(int i = 0; i < sizeof(listN)/sizeof(*listN); i++){
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
    cout << "Appearance Count: " << vMaxCount << endl;
    cout << "Numbers:" << endl;
    // --- search and print the results
    for(int i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        cout << "" << i << ", ";
    }
}

/* ===================================
 * funcD: Count and search from iMin to iMax indices
 *  + take advantage of consecutive same numbers.
 -------------------------------------*/
void funcD(){
    clearCounts();
    int iMin = 0, iMax = 0, vMaxCount = 0;
    int const numCount = sizeof(listN)/sizeof(*listN);
    for(int i = 0; i < numCount; i++){
        auto const iCur = listN[i];
        
        // --- skip the same numbers
        int j = i+1;
        while (iCur == listN[j] && j < numCount) j++;
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
    cout << "Appearance Count: " << vMaxCount << endl;
    cout << "Numbers:" << endl;
    // --- search and print the results
    for(int i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        cout << "" << i << ", ";
    }
}

/* ===================================
 * funcE: Count and search from iMin to iMax indices
 *  + take advantage of consecutive same numbers
 *  + convert to lesser branch mispredictions.
 -------------------------------------*/
void funcE(){
    clearCounts();
    int iMin = 0, iMax = 0, vMaxCount = 0;
    int const numCount = sizeof(listN)/sizeof(*listN);
    for(int i = 0; i < numCount; i++){
        auto const iCur = listN[i];
        
        // --- count ahead the same numbers
        int j = i+1;
        while ((iCur == listN[j]) & (j < numCount)) j++;
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
    cout << "Appearance Count: " << vMaxCount << endl;
    cout << "Numbers:" << endl;
    // --- search and print the results
    for(int i = iMin; i <= iMax; i++){
        if (counts[i] != vMaxCount) continue;
        cout << "" << i << ", ";
    }
}

int main() {

    Timer timer;

    cout << "---func A: Result ---" << endl;
    timer.start();
    funcA();
    timer.stop();
    cout << "\nExecution time: "; timer.printElapsed();

    cout << "\n---func B: Result ---" << endl;
    timer.start();
    funcB();
    timer.stop();
    cout << "\nExecution time: "; timer.printElapsed();

    cout << "\n---func C: Result ---" << endl;
    timer.start();
    funcC();
    timer.stop();
    cout << "\nExecution time: "; timer.printElapsed();


    cout << "\n---func D: Result ---" << endl;
    timer.start();
    funcD();
    timer.stop();
    cout << "\nExecution time: "; timer.printElapsed();


    cout << "\n---func E: Result ---" << endl;
    timer.start();
    funcE();
    timer.stop();
    cout << "\nExecution time: "; timer.printElapsed();


    cout << "\n--- finished! ---" << endl;
    return 0;
}