#include <stdio.h>

// Macro variable argument list

#define PRINT_N(n, ...)                                                        \
  {                                                                            \
    for (int i = 0; i < n; i++)                                                \
      printf(__VA_ARGS__);                                                     \
  }

int main(void) {
  PRINT_N(3, "%d + %d = %d\n", 2, 3, 2 + 3);

  return 0;
}
