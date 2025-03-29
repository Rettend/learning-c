#include <stdio.h>

// String literal vs Char array

int main(void) {
  char *literal = "I am a string literal"; // string literal in read only memory
  char array[] = "I am a string array";    // string literal copied to the stack

  // literal[0] = 'O'; // SEGFAULT
  array[0] = 'O';

  printf("%s\n", literal);
  printf("%s\n", array);

  // Immutable string:
  const char *literal2 = "I am immutable";
  // literal2[0] = 'O'; // Compile time error

  // Mutable string:
  char array2[] = "I am mutable";
  array2[0] = 'O';

  printf("%s\n", literal2);
  printf("%s\n", array2);

  return 0;
}
