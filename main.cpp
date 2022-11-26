#include <iostream>
#include <chrono>
#include <random>
#include "ParallelCountingSort.h"

using namespace std;
using namespace std::chrono;


int main() {
    int* arr = new int[N_ITEMS + 1];
    int* output = new int[N_ITEMS + 1];
    int* count = new int[MAX_VAL + 1];

    for(int i = 0; i<=MAX_VAL; i++)
        count[i] = 0;

    // Generate random numbers
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(0, MAX_VAL);
    arr[1] = MAX_VAL;
    for(int i = 2; i <= N_ITEMS; i++) {
       arr[i] = distribution(gen);
    }

    auto before = high_resolution_clock::now();
    countSort(arr, output, count);
    auto after = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(after - before);
    cout << "Sorting took " << duration.count() << " milliseconds." << endl;

    delete[] arr;
    delete[] output;
    delete[] count;
}