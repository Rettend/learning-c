#include <stdio.h>

// Bit fields

typedef struct {
  unsigned int is_active : 1; // 0-1
  unsigned int priority : 2;  // 0-3
  unsigned int mode : 3;      // 0-7
  unsigned int id : 10;       // 0-1023
  unsigned int user_id : 16;  // 0-65535
} Task;

int main(void) {
  Task task = {1, 3, 4, 10, 10};

  printf("Size of Task: %zu bytes\n", sizeof(Task));
  printf("is_active: %u\n", task.is_active);
  printf("priority: %u\n", task.priority);
  printf("mode: %u\n", task.mode);
  printf("id: %u\n", task.id);
  printf("user_id: %u\n", task.user_id);

  return 0;
}
