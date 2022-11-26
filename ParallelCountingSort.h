const int MAX_VAL = 2147483646;
const int N_ITEMS = 10000;

void countSort(const int *array, int *output, int *count) {
    // Relatively quick loops
    for (int i = 1; i <= N_ITEMS; i++)
        count[array[i]]++;
    for (int i = 1; i <= MAX_VAL; i++)
        count[i] += count[i - 1];

    // Longest loop
    for (int i = N_ITEMS; i >= 1; i--) {
        output[count[array[i]]] = array[i];
        count[array[i]]--;
    }
}