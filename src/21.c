#define _GNU_SOURCE
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Read file line by line

int main(void) {

  FILE *f = fopen("src/21.c", "r");
  if (f == NULL) {
    perror("Error opening file");
    return 1;
  }

  char *line = NULL;
  size_t buff_size = 0;
  int read_size = 0;
  while ((read_size = getline(&line, &buff_size, f)) != -1) {
    line[read_size - 1] = '\0';
    printf("line=%s, malloc'd=%zu\n", line, malloc_usable_size(line)); // REALLY LONG LINE REALLY LONG LINE REALLY LONG LINE
  }

  free(line);
  fclose(f);

  return 0;
}
