#include <stdbool.h>
#include <stdio.h>

// Lookup table

enum num {
  NUM_2 = 0,
  NUM_3,
  NUM_4,
};

static const int squares[] = {
    [NUM_2] = 4,
    [NUM_3] = 9,
    [NUM_4] = 16,
};

enum weekday {
  MONDAY = 0,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY,
};

static const bool is_weekend[] = {
    [MONDAY] = false,   [TUESDAY] = false, [WEDNESDAY] = false,
    [THURSDAY] = false, [FRIDAY] = false,  [SATURDAY] = true,
    [SUNDAY] = true};

static const char *b(bool val) { return val ? "true" : "false"; }

typedef struct {
  int (*operation)(int, int);
  const char *name;
} Operation;

static int add(int a, int b) { return a + b; }
static int sub(int a, int b) { return a - b; }
static int mul(int a, int b) { return a * b; }

static const Operation ops[] = {
    ['a'] = {add, "Addition"},
    ['s'] = {sub, "Subtraction"},
    ['m'] = {mul, "Multiplication"},
};

int main(void) {
  int x = 1;

  printf("%d\n", squares[NUM_2]);
  printf("%d\n", squares[NUM_3]);
  printf("%d\n", squares[NUM_4]);

  printf("%s\n", b(is_weekend[MONDAY]));
  printf("%s\n", b(is_weekend[SATURDAY]));

  int op_id = 'a';
  printf("Choosen op: %s\n", ops[op_id].name);
  printf("Result: %d\n", ops[op_id].operation(x, x));

  return 0;
}
