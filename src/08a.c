#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Task struct with bit fields
typedef struct {
  unsigned int is_active : 1; // 0-1
  unsigned int priority : 2;  // 0-3
  unsigned int mode : 3;      // 0-7
  unsigned int id : 10;       // 0-1023
  unsigned int user_id : 16;  // 0-65535
} Task;

// Function prototypes
Task read_task_from_stdin(void);
void display_task(const Task *task);
int save_task(const Task *task);
int load_task(Task *task);
int list_tasks(void);
void print_help(void);
int quit_program(void);

// Command operation structure
typedef struct {
  int (*operation)(void);
  const char *name;
  const char *description;
} CommandOperation;

// Global task storage for simplicity
static Task current_task;
static const char *DEFAULT_FILENAME = "tasks.bin";

// Function implementations
Task read_task_from_stdin(void) {
  Task task = {0};
  unsigned int temp;

  printf("Enter task details:\n");

  printf("Is active (0-1): ");
  scanf("%u", &temp);
  task.is_active = temp & 1; // Ensure within bounds

  printf("Priority (0-3): ");
  scanf("%u", &temp);
  task.priority = temp & 3;

  printf("Mode (0-7): ");
  scanf("%u", &temp);
  task.mode = temp & 7;

  printf("ID (0-1023): ");
  scanf("%u", &temp);
  task.id = temp & 1023;

  printf("User ID (0-65535): ");
  scanf("%u", &temp);
  task.user_id = temp & 65535;

  current_task = task;
  printf("Task created successfully!\n");
  return task;
}

void display_task(const Task *task) {
  printf("Task details:\n");
  printf("  Size: %zu bytes\n", sizeof(Task));
  printf("  Is active: %u\n", task->is_active);
  printf("  Priority: %u\n", task->priority);
  printf("  Mode: %u\n", task->mode);
  printf("  ID: %u\n", task->id);
  printf("  User ID: %u\n", task->user_id);
}

int save_task(const Task *task) {
  int fd = open(DEFAULT_FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (fd < 0) {
    printf("Error opening file for writing: %s\n", strerror(errno));
    return 0;
  }

  if (write(fd, task, sizeof(Task)) != sizeof(Task)) {
    printf("Error writing to file: %s\n", strerror(errno));
    close(fd);
    return 0;
  }

  close(fd);
  printf("Task saved to %s\n", DEFAULT_FILENAME);
  return 1;
}

int load_task(Task *task) {
  int fd = open(DEFAULT_FILENAME, O_RDONLY);
  if (fd < 0) {
    printf("Error opening file for reading: %s\n", strerror(errno));
    return 0;
  }

  off_t file_size = lseek(fd, 0, SEEK_END);
  if (file_size < (off_t)sizeof(Task)) {
    printf("File is too small or empty\n");
    close(fd);
    return 0;
  }

  // Go back to the beginning and read the last task
  off_t offset = file_size - sizeof(Task);
  lseek(fd, offset, SEEK_SET);

  if (read(fd, task, sizeof(Task)) != sizeof(Task)) {
    printf("Error reading from file: %s\n", strerror(errno));
    close(fd);
    return 0;
  }

  current_task = *task;
  close(fd);
  printf("Task loaded from %s\n", DEFAULT_FILENAME);
  return 1;
}

int list_tasks(void) {
  int fd = open(DEFAULT_FILENAME, O_RDONLY);
  if (fd < 0) {
    printf("Error opening file for reading: %s\n", strerror(errno));
    return 0;
  }

  off_t file_size = lseek(fd, 0, SEEK_END);
  int task_count = file_size / sizeof(Task);

  if (task_count == 0) {
    printf("No tasks found in file\n");
    close(fd);
    return 0;
  }

  printf("Found %d task(s) in file:\n\n", task_count);

  lseek(fd, 0, SEEK_SET); // Go back to beginning
  Task task;
  int index = 0;

  while (read(fd, &task, sizeof(Task)) == sizeof(Task)) {
    printf("Task #%d:\n", ++index);
    display_task(&task);
    printf("\n");
  }

  close(fd);
  return 1;
}

void print_help(void) {
  printf("Task Manager Commands:\n");
  printf("  c - Create new task\n");
  printf("  d - Display current task\n");
  printf("  s - Save current task to file\n");
  printf("  l - Load last task from file\n");
  printf("  a - List all tasks\n");
  printf("  h - Help\n");
  printf("  q - Quit\n");
  return;
}

int quit_program(void) {
  printf("Goodbye!\n");
  exit(0);
  return 1; // Never reached
}

// Command lookup table
static const CommandOperation commands[] = {
    ['c'] = {(int (*)(void))read_task_from_stdin, "Create",
             "Create a new task"},
    ['d'] = {(int (*)(void))display_task, "Display", "Display current task"},
    ['s'] = {(int (*)(void))save_task, "Save", "Save task to file"},
    ['l'] = {(int (*)(void))load_task, "Load", "Load task from file"},
    ['a'] = {list_tasks, "List", "List all tasks"},
    ['h'] = {(int (*)(void))print_help, "Help", "Display help"},
    ['q'] = {quit_program, "Quit", "Exit the program"},
};

int main(void) {
  char choice;

  printf("Task Manager - Bit Fields Demo\n");
  print_help();

  // Initialize default task
  current_task = (Task){1, 1, 1, 1, 1};

  while (1) {
    printf("\nEnter command (h for help): ");
    scanf(" %c", &choice);

    // Look up the command in our table
    if (choice >= 0 && choice < (int)sizeof(commands) / sizeof(commands[0]) &&
        commands[(int)choice].operation != NULL) {
      if (choice == 'd') {
        display_task(
            &current_task); // Special case for display which needs a pointer
      } else {
        commands[(int)choice].operation();
      }
    } else {
      printf("Unknown command: %c\n", choice);
      print_help();
    }
  }

  return 0;
}
