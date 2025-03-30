#include <stdio.h>

// Macros

#define DIV_bad(x, y) x / y
#define DIV_still_bad(x, y) (x / y)
#define DIV(x, y) ((x) / (y))

#define SUM_ALL_bad(start, end)                                                \
  int sum = 0;                                                                 \
  for (int i = start; i < end; i++)                                            \
    sum += i;                                                                  \
  printf("Sum: %d\n", sum)

#define SUM_ALL(start, end)                                                    \
  {                                                                            \
    int sum = 0;                                                               \
    for (int i = start; i < end; i++)                                          \
      sum += i;                                                                \
    printf("Sum: %d\n", sum);                                                  \
  }

int main(void) {
  // DIV_bad expands to 10 / 2 + 3, which is (10/2) + 3 = 8
  printf("%d\n", DIV_bad(10, 2) + 3);
  printf("%d\n\n", 10 / 2 + 3);

  // DIV_still_bad with 10, 2+1 expands to (10 / 2+1), which is (10/2) + 1 = 6
  printf("%d\n", DIV_still_bad(10, 2 + 1));
  printf("%d\n\n", (10 / 2 + 1));

  // DIV with 10, 2+1 expands to ((10) / (2+1)), which is 10/3 = 3
  printf("%d\n", DIV(10, 2 + 1));
  printf("%d\n\n", ((10) / (2 + 1)));

  int sum = 0;

  // SUM_ALL_bad(1, 10); // Redefinition of 'sum
  SUM_ALL(1, 10);

  return 0;
}
