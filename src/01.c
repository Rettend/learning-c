#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function type, Function pointers, Predicate functions

typedef int (*Function)(int, int);

int add(int x, int y) { return x + y; }
bool is_even(int x) { return x % 2 == 0; }

int count_if(int *arr, int A, bool (*predicate)(int)) {
  int count = 0;
  for (int i = 0; i < A; i++) {
    if (predicate(arr[i]))
      count++;
  }
  return count;
}

int compar(const void *x1, const void *x2) { return *(int *)x1 - *(int *)x2; }

int main(void) {
  int (*f)(int, int) = add;
  printf("%d\n", f(3, 4));

  Function g = add;
  printf("%d\n", g(3, 4));

  int xs[] = {3, 7, 1, 9, 0, 4, 6, 8, 2, 5};
  printf("%d\n", count_if(xs, sizeof(xs) / sizeof(xs[0]), is_even));

  for (int i = 0; i < 10; i++)
    printf("%d ", xs[i]);
  printf("\n");

  qsort(xs, 10, sizeof(int), compar);

  for (int i = 0; i < 10; i++)
    printf("%d ", xs[i]);
  printf("\n");

  return 0;
}
