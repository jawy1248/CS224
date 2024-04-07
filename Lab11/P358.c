
#include <stdio.h>

long decode2(long x, long y, long z){
    y = y - z;
    x = x * y;
    return (((y << 63) >> 63) ^ x);
}

int main(){
    printf("%ld", decode2(14123, 21423, 34123));
}