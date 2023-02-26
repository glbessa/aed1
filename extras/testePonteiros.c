#include <stdio.h>

int main() {
    int x = 12345;
    void *y = &x;

    printf("%d\n", *(y+1));

    return 0;
}