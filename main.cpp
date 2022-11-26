#include <iostream>
#include <chrono>
#include <random>
#include "ParallelCountingSort.h"
#include "pthread.h"

using namespace std;
using namespace std::chrono;

int* arr = new int[N_ITEMS + 1];
int* output = new int[N_ITEMS + 1];
int* count = new int[MAX_VAL + 1];

int workingThread = 0;

void assignArrays(){
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
}

void* mergeCount(void* arg){
    int thread_part = workingThread++;

    int low = thread_part * (N_ITEMS / N_THREADS); // thread part is 0, 1, 2, 3
    int high = (thread_part + 1) * (N_ITEMS / N_THREADS) - 1;


    for (int i = low; i <= high; i++)
        count[arr[i]]++;
    for (int i = low; i <= high; i++)
        count[i] += count[i - 1];

    return nullptr;
}

void* mergeAssign(void* arg) {
    int thread_part = workingThread++;

    int low = thread_part * (N_ITEMS / N_THREADS); // thread part is 0, 1, 2, 3
    int high = (thread_part + 1) * (N_ITEMS / N_THREADS) - 1;


    for (int i = high; i >= low; i--) {
        output[count[arr[i]]] = arr[i];
        count[arr[i]]--;
    }

    pthread_exit(nullptr);

    return nullptr;
}

void runMultiThread(){
    assignArrays();


    for (int i = 1; i <= N_ITEMS; i++)
        count[arr[i]]++;
    for (int i = 1; i <= MAX_VAL; i++)
        count[i] += count[i - 1];

    cout << "Finished prelim operations\n";

    auto before = high_resolution_clock::now();

    pthread_t threads[N_THREADS];
    for (unsigned long long & thread : threads)
        pthread_create(&thread, nullptr, mergeAssign, (void *) nullptr);

//    for (unsigned long long thread: threads)
//        pthread_join(thread, nullptr);

    auto after = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(after - before);
    cout << "Final aspect of sorting took " << duration.count() << " milliseconds." << endl;

    for(int i=100;i<150;i++)
        cout << arr[i] << " ";

    delete[] arr;
    delete[] output;
    delete[] count;
}

int main(){
    runMultiThread();
}