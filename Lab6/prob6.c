#include <stdio.h>
int main() {
    int a = 0;
    char *s_ptr = (char *)&a;
    scanf("%s", s_ptr);
    printf("a = %d\n", a);
    return 0;
}