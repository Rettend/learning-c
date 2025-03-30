#include <stdio.h>

// Anonymous struct and array

typedef struct {
  int x;
  int y;
} Vector;

int scaled_sum(Vector v, int s) { return (v.x + v.y) * s; }

int sum_array(int *arr, int A) {
  int s = 0;
  for (int i = 0; i < A; i++)
    s += arr[i];
  return s;
}

int main(void) {

  Vector v1 = {2, 3};
  printf("%d\n", scaled_sum(v1, 4));

  printf("%d\n", scaled_sum((Vector){2, 3}, 4));
  printf("%d\n", sum_array((int[]){1, 2, 3}, 3));

  return 0;
}
