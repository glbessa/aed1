#include <stdio.h>
#include <stdlib.h>

int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize);
int maxNumLimited(int *nums, int length, int lessThanThis);
void sort(int *nums, int numsSize);
//int searchMax(int *nums, int start, int end);
void printArray(int *array, int length);

int main() {
    int n = 4, k = 2;
    //int array[] = {2,1,3,3};
    //int array[] = {-1,-2,3,4};
    //int array[] = {3,4,3,3};
    int array[] = {10, 3,4,3,-1};

    int *seq = maxSubsequence(array, n, k, &k);

    printArray(seq, k);

    return 0;
}

int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize) {
    int *numsCopy = (int *) malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        numsCopy[i] = nums[i];
    }

    int *maxSeq = (int *) malloc(sizeof(int) * k);
    if (!maxSeq) {
        perror("Error while allocating max sequence");
        exit(-1);
    }

    returnSize = (int *) malloc(sizeof(int));
    if (!returnSize) {
        perror("Error while allocating return size");
        exit(-1);
    }
    *returnSize = k;

    maxSeq[0] = maxNumLimited(nums, numsSize, 106);
    int minMaxNumPos = maxSeq[0];
    nums[maxSeq[0]] = -106;
    for (int i = 1; i < k; i++) {
        maxSeq[i] = maxNumLimited(nums, numsSize, numsCopy[minMaxNumPos]);
        nums[maxSeq[i]] = -106;
        if (numsCopy[maxSeq[i]] < numsCopy[minMaxNumPos])
            minMaxNumPos = i;
    }

    sort(maxSeq, k);

    for (int i = 0; i < k; i++) {
        maxSeq[i] = numsCopy[maxSeq[i]];
    }

    return maxSeq;
}

int maxNumLimited(int *nums, int length, int lessOrEqualThanThis) {
    int maxPos = 0;
    for (int i = 1; i < length; i++) {
        if (nums[i] > nums[maxPos] && nums[i] <= lessOrEqualThanThis)
            maxPos = i;
    }
    return maxPos;
}

void sort(int *nums, int numsSize) {
    int i, j, temp;

    for (i = 0; i < numsSize - 1; i++) {
        for (j = i + 1; j < numsSize; j++) {
            if (nums[i] > nums[j]) {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
}
/*
int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize) {
    int *maxSeq = (int *) malloc(sizeof(int) * k);
    if (!maxSeq) {
        perror("Error while allocating max sequence");
        exit(-1);
    }

    returnSize = (int *) malloc(sizeof(int));
    if (!returnSize) {
        perror("Error while allocating return size");
        exit(-1);
    }
    *returnSize = k;

    int divisionsLenght = numsSize / k;

    for (int i = 0; i < k - 1; i++) {
        maxSeq[i] = searchMax(nums, i * divisionsLenght, (i + 1) * divisionsLenght);
    }

    maxSeq[k - 1] = searchMax(nums, (k - 1) * divisionsLenght, numsSize);

    return maxSeq;
}

int searchMax(int *nums, int start, int end) {
    int max = nums[start];
    for (int i = start + 1; i < end; i++) {
        if (max < nums[i])
            max = nums[i];
    }

    return max;
}
*/

void printArray(int *array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%i ", array[i]);
    }
}