#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Void pointers

void map(void *arr, size_t A, size_t arr_sizes, void (*f)(void *)) {
  uint8_t *arr_bytes = (uint8_t *)arr;
  for (size_t i = 0; i < A; i++)
    f(&arr_bytes[i * arr_sizes]);
}

void square(void *x) { *(int *)x *= *(int *)x; }

int main(void) {
  int xs[] = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; i++)
    printf("%d ", xs[i]);
  printf("\n");

  map(xs, 5, sizeof(int), square);

  for (int i = 0; i < 5; i++)
    printf("%d ", xs[i]);
  printf("\n");

  return 0;
}
