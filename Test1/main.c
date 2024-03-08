#include <stdio.h>
int main(void) {
    int i[2] = {2, 4};
    char s[6] = "01234";
    printf("i = %p\n", i);
    printf("s = %p\n", s);
    scanf("%s", s);
    printf("i[0] = 0x%x\n", i[0]);
    printf("i[1] = 0x%x\n", i[1]);
    printf("s = %s\n", s);
    return 0;
}