
#include <stdio.h>

/*
 * x = %rdi
 * n = %rsi
 * result = %rax
 * mask = %rdx
 *
 * result = 0
 * mask = 1
 *
 * mask != 0
 *
 * mask = mask << n
 *
 * result |= (x & mask)
 *
 */

long loop(long x, int n){
    long result = 0;
    long mask;
    for(mask = 1; mask != 0 ; mask = mask << n ){
        result |= (x & mask);
    }
    return result;
}

int main(){
    printf("%ld", loop(15, 3));
}