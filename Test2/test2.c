
#include <stdio.h>

long int rfun(long int x, long int y) {
    long int nx = x - 1;
    long int ny = y - 2;
    long int rv = 0;
    if (x == 0)
        return 0;

    rv = rfun(nx, ny);
    return rv;
}

int main() {
    long int test = rfun(3, 6);
    printf("value: %ld\n", test);
    return 1;
}