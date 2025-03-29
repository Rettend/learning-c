#include <stdio.h>

// Function type, Function pointers, Predicate functions

int add(int x, int y) { return x + y; }

int main() {
  int (*a)(int, int) = add;

  printf("%d\n", a(3, 4));
}
