#include <stdio.h>

// Error handling

int main(void) {
  FILE *f = fopen("src/20.c", "r");
  if (f == NULL) {
    perror("Error opening file");
    return 1;
  }

  char c;
  while ((c = fgetc(f)) != EOF)
    fputc(c, stdout);

  fclose(f);

  return 0;
}
