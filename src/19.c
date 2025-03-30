#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Split string

int main(void) {
  char s[] = "1,2,3,4,5";

  char *token = strtok(s, ",");
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
  }

  printf("original: %s\n\n", s);

  const char *a = "1,2,3,4,5";

  char *copy = strdup(a);
  if (copy == NULL) {
    fprintf(stderr, "strdup failed!\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(copy, ",");
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
  }
  free(copy);

  printf("original: %s\n", a);

  return 0;
}
