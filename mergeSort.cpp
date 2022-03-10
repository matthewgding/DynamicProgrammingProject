/**************************************************************************
 * Created by Matthew on 3/10/2022.
 * This implementation has been adapted from the implementation written by
 * Mayank Tyagi and Joshua Estes on GeeksforGeeks.
 * https://www.geeksforgeeks.org/merge-sort/
 **************************************************************************/

#include <iostream>
using namespace std;

// merge(): Merges two sub-arrays of values[] and lines[]
// Inputs: The int array to be sorted, the string array to be sorted with the same
// indices as the int array, the left index of the sub-arrays, the midpoint of the
// sub-arrays, the right index of the sub-arrays

// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int values[], string lines[], int const left, int const mid, int const right) {
    const int subArrayOne = mid - left + 1;
    const int subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftValues = new int[subArrayOne], *rightValues = new int[subArrayTwo];
    auto *leftLines = new string[subArrayOne], *rightLines = new string[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++) {
        leftValues[i] = values[left + i];
        leftLines[i] = lines[left + i];
    }
    for (int j = 0; j < subArrayTwo; j++) {
        rightValues[j] = values[mid + 1 + j];
        rightLines[j] = lines[mid + 1 + j];
    }

    int indexOfSubArrayOne = 0, // Initial index of first sub-array
    indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftValues[indexOfSubArrayOne] <= rightValues[indexOfSubArrayTwo]) {
            values[indexOfMergedArray] = leftValues[indexOfSubArrayOne];
            lines[indexOfMergedArray] = leftLines[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            values[indexOfMergedArray] = rightValues[indexOfSubArrayTwo];
            lines[indexOfMergedArray] = rightLines[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of the left sub-arrays, if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        values[indexOfMergedArray] = leftValues[indexOfSubArrayOne];
        lines[indexOfMergedArray] = leftLines[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of the right sub-arrays, if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        values[indexOfMergedArray] = rightValues[indexOfSubArrayTwo];
        lines[indexOfMergedArray] = rightLines[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

// mergeSort(): Performs the splitting and merging of mergesort
// Inputs: The int array to be sorted, the string array to be sorted with the same
// indices as the int array, the left index of the arrays, the right index of
// the arrays
void mergeSort(int values[], string lines[], int const begin, int const end) {
    // Return when the array has been split all the way to its end
    if (begin >= end) {
        return;
    }

    // Determine the midpoint of the arrays
    auto mid = begin + (end - begin) / 2;
    // Split the array recursively
    mergeSort(values, lines, begin, mid);
    mergeSort(values, lines, mid + 1, end);
    merge(values, lines, begin, mid, end);
}

