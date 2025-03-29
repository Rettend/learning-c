#include <stdio.h>

// Sizeof

#define ARRAY_LEN(x) sizeof(x) / sizeof(x[0])

int main(void) {
  int a = 1;
  int xs[] = {1, 2, 3, 4, 5};
  int *xs_p = xs;

  printf("%zu\n", sizeof(int));
  printf("%zu\n", sizeof(a));
  printf("%zu\n", sizeof(xs));
  printf("%zu\n", sizeof(xs_p));
  printf("%zu\n", ARRAY_LEN(xs));

  return 0;
}
