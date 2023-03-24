#include <stdio.h>

int main() {
    int x = 12345;
    void *y = &x;

    //printf("%d\n", *(y+1));
    printf("%i\n", sizeof(void *));
    printf("%i\n", sizeof(void **));

    return 0;
}