#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[6] = {5, 2, 6, 1, 4, 3};

    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (array[i] > array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    for (int i = 0; i < 6; i++){
        printf("%i\n", *(array+i));
    }

    return 0;
}