#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <assert.h>
#include <span>
#include <string>
#include "sorts.h"
#include "profile.h"

using namespace std;

void quickSortTester(size_t cnt) {
    const size_t CNT = cnt;
    vector<int> v(CNT);

    for (int i = 0; i < CNT; i++)
        v[i] = CNT - i;
    { LOG_DURATION("Quick Sort (unsorted, " + to_string(cnt) + " elements)")
        quickSort(v);
    }
    assert(is_sorted(begin(v), end(v)));

    iota(begin(v), end(v), 1);
    { LOG_DURATION("Quick Sort (sorted, " + to_string(cnt) + " elements)")
        quickSort(v);
    }
    assert(is_sorted(begin(v), end(v)));

    generate(begin(v), end(v), rand);
    { LOG_DURATION("Quick Sort (random, " + to_string(cnt) + " elements)")
        quickSort(v);
    }
    assert(is_sorted(begin(v), end(v)));
}

void mergeSortTester(size_t cnt) {
    const size_t CNT = cnt;
    vector<int> v(CNT);

    for (int i = 0;i < CNT;i++)
        v[i] = CNT - i;
    { LOG_DURATION("Merge Sort (unsorted, " + to_string(cnt) + " elements)")
        mergeSort(v);
    }
    assert(is_sorted(begin(v), end(v)));

    iota(begin(v), end(v), 1);
    { LOG_DURATION("Merge Sort (sorted, " + to_string(cnt) + " elements)")
        mergeSort(v);
    }
    assert(is_sorted(begin(v), end(v)));

    generate(begin(v), end(v), rand);
    { LOG_DURATION("Merge Sort (random, " + to_string(cnt) + " elements)")
        mergeSort(v);
    }
    assert(is_sorted(begin(v), end(v)));
}

int main() {
    quickSortTester(1e4);
    quickSortTester(1e5);
    quickSortTester(1e6);
    mergeSortTester(1e4);
    mergeSortTester(1e5);
    mergeSortTester(1e6);
    //quickSortTester(1e8);
    return 0;
}