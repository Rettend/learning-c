#include <stdbool.h>
#include <stdio.h>

// Bit flags

int f(int x, bool is_added, bool is_squared, bool is_not) {
  if (is_added)
    x += x;
  if (is_squared)
    x *= x;
  if (is_not)
    x = ~x;
  return x;
}

typedef enum {
  FLAG_ADD = 1 << 0, // 0001
  FLAG_SQR = 1 << 1, // 0010
  FLAG_NOT = 1 << 2  // 0100
} t_flag;

int g(int x, t_flag flags) {
  if (flags & FLAG_ADD)
    x += x;
  if (flags & FLAG_SQR)
    x *= x;
  if (flags & FLAG_NOT)
    x = ~x;

  // remove FLAG_ADD:
  // flags &= ~FLAG_ADD;

  return x;
}

int main(void) {
  printf("%d\n", f(1234, false, false, false));
  printf("%d\n", f(1234, true, false, false));
  printf("%d\n", f(1234, false, true, true));

  printf("---\n");

  printf("%d\n", g(1234, 0));
  printf("%d\n", g(1234, FLAG_ADD));
  printf("%d\n", g(1234, FLAG_SQR | FLAG_NOT));

  return 0;
}
