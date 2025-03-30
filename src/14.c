#include <stdio.h>

// Macro stringify and tokenize

#define ADD(x, y) printf("%s + %s = %d\n", #x, #y, x + y)

#define PREFIX(name) new_##name

#define GENERIC_ADD(type)                                                      \
  type add_##type(type x, type y) { return x + y; }

GENERIC_ADD(int)
GENERIC_ADD(float)
GENERIC_ADD(long)

int main(void) {

  int first = 2;
  int second = 3;
  ADD(first, second);

  int PREFIX(num) = 2;
  printf("%d\n", new_num);

  printf("%d\n", add_int(3, 4));
  printf("%f\n", add_float(3.2, 4.2));
  printf("%ld\n", add_long(3L, 4L));

  return 0;
}
