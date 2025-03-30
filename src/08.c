#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Bit fields

typedef struct {
  unsigned int is_active : 1; // 0-1
  unsigned int priority : 2;  // 0-3
  unsigned int mode : 3;      // 0-7
  unsigned int id : 10;       // 0-1023
  unsigned int user_id : 16;  // 0-65535
} Task;

static const char *FILENAME = "src/08.bin";

int main(void) {
  Task task = {1, 3, 4, 10, 10};
  Task task2 = {};

  int fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  write(fd, &task, sizeof(Task));
  lseek(fd, 0, SEEK_SET);
  read(fd, &task2, sizeof(Task));
  close(fd);

  printf("Size of Task: %zu bytes\n", sizeof(Task));
  printf("is_active: %u\n", task2.is_active);
  printf("priority: %u\n", task2.priority);
  printf("mode: %u\n", task2.mode);
  printf("id: %u\n", task2.id);
  printf("user_id: %u\n", task2.user_id);

  return 0;
}
