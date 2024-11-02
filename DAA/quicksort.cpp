#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void deterministicQuickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    deterministicQuickSort(arr, left, j);
    deterministicQuickSort(arr, i, right);
}

void randomizedQuickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivotIndex = left + rand() % (right - left + 1);
    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[right]); 
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]); // Move pivot to its final place

    randomizedQuickSort(arr, left, i - 1);
    randomizedQuickSort(arr, i + 1, right);
}

int main() {
    srand(time(0)); 

    vector<int> arr = {10, 7, 8, 9, 1, 5};
    vector<int> arr2 = arr;

    deterministicQuickSort(arr, 0, arr.size() - 1);
    randomizedQuickSort(arr2, 0, arr2.size() - 1);

    cout << "Deterministic Quick Sort: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    cout << "Randomized Quick Sort: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";

    return 0;
}
