#include <stdio.h>

int main() {
    // // Problem 2b
    // printf("--------------- Problem 2b ---------------\n");
    // unsigned char x = 0x5a;
    // unsigned char y = 0x73;
    // printf("x & y:     0x%02x\n", x & y);
    // printf("x | y:     0x%02x\n", x | y);
    // printf("~x | ~y:   0x%02x\n", ~x | ~y);
    // printf("x & !y:    0x%02x\n", x & !y);
    // printf("x && y:    0x%02x\n", x && y);
    // printf("x || y:    0x%02x\n", x || y);
    // printf("!x || !y:  0x%02x\n", !x || !y);
    // printf("x && ~y:   0x%02x\n", x && ~y);
    // printf("------------------------------------------\n\n");

    // // Problem 2c
    // printf("--------------- Problem 2c ---------------\n");
    // int z = 0x12345678;
    // printf("x: 0x%08x\n", z);
    // printf("5th nibble of x: 0x%02x\n\n", (z >> 16) & 0xf);

    // int a = 0x12345678;
    // printf("x: 0x%08x\n", a);
    // // a =| (1 << 17) | (1 << 19);
    // printf("x (18th & 20th bit = 1): 0x%08x\n", a | (1 << 17) | (1 << 19));
    // printf("------------------------------------------\n\n");

    // // Problem 3
    // printf("--------------- Problem 3 ---------------\n");
    // char c[] = {0x3c, 0x1a, 0x8d, 0xff, 0x88, 0x4e, 0x9c, 0xd4};
    // void *p = c;

    // char *h = (char *)p;
    // printf("--- char *a = (char *)p ---\n");
    // printf("Hex:       %x\n", *h);
    // printf("Char:      %c\n", *h);
    // printf("Unsigned:  %u\n", *h);
    // printf("Signed:    %d\n", *h);
    // printf("-----------------------------------------\n\n");

    // // Problem 3
    // printf("--------------- Problem 4 ---------------\n");
    // unsigned char d[] = {0x37, 0x3f, 0xd5, 0x12, 0x34, 0xf2, 0x43, 0x01, 0xf7, 0xff, 0x94, 0x79, 0x9e, 0x88, 0xba, 0x50};
    // void *s = d;

    // char *r = (char *)s;
    // printf("Unsigned:  %u\n", 0xf2);
    // printf("Signed:    %d\n\n", *(r + 2));

    // int *g = (int *)s;
    // long *q = (long *)s;
    // printf("Ptr Pointer:    %p\n", s);
    // printf("Ptr Pointer:    %p\n", (s + 1));
    // printf("Char Pointer:   %p\n", r);
    // printf("Char Pointer:   %p\n", (r + 1));
    // printf("Int Pointer:    %p\n", g);
    // printf("Int Pointer:    %p\n", (g + 1));
    // printf("Long Pointer:   %p\n", q);
    // printf("Long Pointer:   %p\n", (q + 1));
    // printf("-----------------------------------------\n\n");

    // Problem 3
    printf("--------------- Problem 5 ---------------\n");
    unsigned char u = 0;
    u = u - 1;
    int a = (int)u;
    printf("%d\n", a);
    printf("-----------------------------------------\n\n");

    return 0;
}