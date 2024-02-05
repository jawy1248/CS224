#include <stdio.h>

#define SIZE 24

int main() {
  char str[SIZE];
  int *i_ptr = (int *)str;
  int *i_end = i_ptr + SIZE/sizeof(int);

  printf("Type input:\n");
  scanf("%x %x %x %x %x %x", i_ptr, i_ptr + 1, i_ptr + 2, i_ptr + 3, i_ptr + 4, i_ptr + 5);
  printf("Thank you.\n");
  
  while (i_ptr < i_end) {
    printf("i_ptr = %p\t *i_ptr = 0x%x\n", i_ptr, *i_ptr);
    ++i_ptr;
  }

  printf("str = %s\n", str);
  return 0;
}
