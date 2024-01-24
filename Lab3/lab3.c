#include <stdio.h>

int main()
{
    // unsigned char u = ?;
    unsigned char u = 67;       // with dec
    unsigned char c = 'C';      // with ASCII
    unsigned char l = 0x43;     // with hex

    // int
    int x = 12;

    // double
    double y = 3.14;

    // Print char
    printf("char as char: %c\n", u);
    printf("char as hex: %x\n", u);
    printf("char as dec: %d\n", u);

    // Print int
    printf("int as char: %c\n", x);
    printf("int as hex: %x\n", x);
    printf("int as dec: %d\n", x);

    // Print double
    printf("double as char: %c\n", y);
    printf("double as hex: %x\n", y);
    printf("double as dec: %d\n", y);
}