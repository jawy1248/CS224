
#include <stdio.h>

/*
 * |-----------|
 * |           | <- (unused space)
 * |-----------| <- %rsp + 104
 * |     z     | <- %rsp + 24
 * |-----------|
 * |     y     | <- %rsp + 8
 * |-----------|
 * |     x     | <- %rsp
 * |-----------| <- %rsp
 *
 * strA s
 *
 * Accesses then
 *
 */

void sum_col(long n, long A[NR(n)][NC(n)], long j){
    long i;
    long result = 0;
    for (i = 0; i < NR(n); i++)
        result += A[i][j];
    return result;
}

int main(){
    printf("%ld", loop(15, 3));
}
