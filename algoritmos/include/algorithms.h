#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define BCK_LEN 5

typedef struct bucket_t bucket_t;
struct bucket_t {
    int length;
    int values[BCK_LEN];
};

// Prototypes -----------------------------------------
int *WorstCase(int n);
int *BestCase(int n);
int *RandomCase(int n);
void PrintArray(int *array, int n);

void insertion_sort(int *array, int length);

void selection_sort(int *array, int length);

void merge_sort(int *array, int start, int end);
void merge(int *array, int start, int middle, int end);

void quick_sort(int *array, int left, int right);

void heap_sort(int *array, int length);
void create_heap(int *array, int start, int end);

void bucket_sort(int *array, int length);
// ----------------------------------------------------

// Arrays generators ----------------------------------
int *WorstCase(int n) {
    int *array = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        *(array + i) = n - i;
    }

    return array;
}

int *BestCase(int n) {
    int *array = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        *(array + i) = i;
    }

    return array;
}

int *RandomCase(int n) {
    int *array = (int *) malloc(sizeof(int) * n);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        *(array + i) = rand() % n;
    }

    return array;
}

void PrintArray(int *array, int n) {
    printf("[");
    for (int i = 0; i < n; i++){
        if (i != 0)
            printf(", ");
        printf("%i", *(array+i));
    }
    printf("]\n");
}

// -----------------------------------------------------
// MergeSort -------------------------------------------
void merge_sort(int *array, int start, int end) {
    if (start >= end)
        return;

    int middle;
    middle = floor((start + end) / 2);

    merge_sort(array, start, middle);
    merge_sort(array, middle + 1, end);
    merge(array, start, middle, end);
}

void merge(int *array, int start, int middle, int end) {
    int *temp, p1, p2, length, i, j, k, fim1=0, fim2=0;
    length = end - start + 1;
    p1 = start;
    p2 = middle + 1;

    temp = (int *) malloc(length * sizeof(int));

    if (!temp)
        return;

    for (i = 0; i < length; i++) {
        if (!fim1 && !fim2) {
            if (array[p1] < array[p2])
                temp[i] = array[p1++];
            else
                temp[i] = array[p2++];

            if (p1 > middle) fim1 = 1;
            if (p2 > end) fim2 = 1;
        }
        else {
            if (!fim1)
                temp[i] = array[p1++];
            else
                temp[i] = array[p2++];
        }
    }

    // Copy auxiliary to original
    for (j = 0, k = start; j < length; j++, k++) {
        array[k] = temp[j];
    }

    free(temp);
}

// -------------------------------------------------
// QuickSort ---------------------------------------
void quick_sort(int *array, int left, int right) {
    if (array == NULL)
        return;

    if (left > right)
        return;

    int middle, temp, i, j;
    i = left;
    j = right;

    middle = array[(left + right) / 2];

    do {
        while (array[i] < middle)
            i++;
        while (middle < array[j])
            j--;

        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j)
        quick_sort(array, left, j);
    if (i < right)
        quick_sort(array, i, right);
}

// ---------------------------------------------
// HeapSort ------------------------------------
void heap_sort(int *array, int length) {
    int i, aux;

    // Create heap from data
    for (i = (length - 1)/2; i >= 0; i--) {
        create_heap(array, i, length - 1);
    }

    for (i = length - 1; i >= 1; i--) {
        // Take greater elemtent of heap and put it at its specific position in the array
        aux = array[0];
        array[0] = array[i];
        array[i] = aux;
        // Heap reconstruction
        create_heap(array, 0, i - 1);
    }
}

void create_heap(int *array, int start, int end) {
    int aux = array[start]; // parent
    int j = start * 2 + 1;
    
    while (j <= end) {
        if (j < end) {
            // If parent has two children, who is greater?
            if (array[j] < array[j + 1]) {
                j++;
            }
        }
        // Child turned into parent if child greater than parent
        if (aux < array[j]) {
            array[start] = array[j];
            start = j;
            j = 2 * start + 1;
        } else {
            j = end + 1;
        }
    }
    // Last parent at last child position
    array[start] = aux;
}
// ----------------------------------------

void bucket_sort(int *array, int length) {
    int min, max, num_buckets, i, j, pos;
    bucket_t *buckets;

    min = max = array[0];
    for (i = 1; i < length; i++) {
        if (array[i] < min)
            min = array[i];
        if (array[i] > max)
            max = array[i];
    }

    num_buckets = (max - min) / BCK_LEN + 1;
    buckets = (bucket_t *) malloc(sizeof(bucket_t) * num_buckets);

    for (i = 0; i < num_buckets; i++) {
        buckets[i].length = 0;
    }

    for (i = 0; i < length; i++) {
        pos = (array[i] - min) / BCK_LEN;
        buckets[pos].values[buckets[pos].length] = array[i];
        buckets[pos].length++;
    }

}

#endif