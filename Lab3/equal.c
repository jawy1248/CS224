#include <stdio.h>

int main()
{
    unsigned char u = 67;
    unsigned char c = 'C';
    unsigned char l = 0x43;
    
    if ((u == c) && (c == l)) {
        printf("They are the same!\n");
    }
    else {
        printf("They are different!\n");
    }
    return 0;
}
