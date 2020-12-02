#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <assert.h>
#include <span>
#include <string>
#include "sorts.h"
#include "parallelsorts.h"
#include "profile.h"

using namespace std;

template<class Func>
void sortTester(size_t cnt, Func sorter, const string& sort_name) {
    const size_t CNT = cnt;
    vector<int> v(CNT);

    for (int i = 0; i < CNT; i++)
        v[i] = CNT - i;
    { LOG_DURATION(sort_name + " (unsorted, " + to_string(cnt) + " elements)")
        sorter(v);
    }
    bool us = is_sorted(begin(v), end(v));

    iota(begin(v), end(v), 1);
    { LOG_DURATION(sort_name + " (sorted, " + to_string(cnt) + " elements)")
        sorter(v);
    }
    bool s = is_sorted(begin(v), end(v));

    generate(begin(v), end(v), rand);
    { LOG_DURATION(sort_name + " (random, " + to_string(cnt) + " elements)")
        sorter(v);
    }
    bool rs = is_sorted(begin(v), end(v));
    if (us && s && rs)
        clog << "CORRECT!";
    else
        clog << "INCORRECT!";
    clog << endl << endl;
}

int main() {
    sortTester(1e4, quickSort<vector<int>&>, "Quick Sort");
    sortTester(1e5, quickSort<vector<int>&>, "Quick Sort");
    sortTester(1e6, quickSort<vector<int>&>, "Quick Sort");

    sortTester(1e4, mergeSort<vector<int>&>, "Merge Sort");
    sortTester(1e5, mergeSort<vector<int>&>, "Merge Sort");
    sortTester(1e6, mergeSort<vector<int>&>, "Merge Sort");
    
    sortTester(1e4, multithread::quickSort<vector<int>&>, "Quick Sort (multithread)");
    sortTester(1e5, multithread::quickSort<vector<int>&>, "Quick Sort (multithread)");
    sortTester(1e6, multithread::quickSort<vector<int>&>, "Quick Sort (multithread)");

    sortTester(1e4, multithread::mergeSort<vector<int>&>, "Merge Sort (multithread)");
    sortTester(1e5, multithread::mergeSort<vector<int>&>, "Merge Sort (multithread)");
    sortTester(1e6, multithread::mergeSort<vector<int>&>, "Merge Sort (multithread)");

    return 0;
}