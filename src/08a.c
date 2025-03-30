#include "08a.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  unsigned int is_active : 1; // 0-1
  unsigned int priority : 2;  // 0-3
  unsigned int mode : 3;      // 0-7
  unsigned int id : 10;       // 0-1023
  unsigned int user_id : 16;  // 0-65535
} Task;

int read_task_from_stdin(void);
void display_task(const Task *task);
int save_task(const Task *task);
int load_task(Task *task);
int list_tasks(void);
int print_help(void);
int quit_program(void);

typedef struct {
  int (*operation)(void);
  const char *name;
  const char *description;
} CommandOperation;

static Task current_task;
static const char *FILENAME = "src/08a.bin";

int read_task_from_stdin(void) {
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

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  current_task = task;
  printf("Task created successfully!\n");
  return 1;
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
  int fd = openCheck(FILENAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
  writeCheck(fd, task, sizeof(Task));
  closeCheck(fd);
  printf("Task saved to %s\n", FILENAME);
  return 1;
}

int load_task(Task *task) {
  int fd = open(FILENAME, O_RDONLY, 0);
  if (fd < 0) {
    printf("Cannot load task: File not found or cannot be opened\n");
    return 0;
  }

  off_t file_size = lseekCheck(fd, 0, SEEK_END);
  if (file_size < (off_t)sizeof(Task)) {
    printf("File is too small or empty\n");
    closeCheck(fd);
    return 0;
  }

  // Go back to the beginning and read the last task
  off_t offset = file_size - sizeof(Task);
  lseekCheck(fd, offset, SEEK_SET);
  readCheck(fd, task, sizeof(Task));

  current_task = *task;
  closeCheck(fd);
  printf("Task loaded from %s\n", FILENAME);
  return 1;
}

int list_tasks(void) {
  int fd = open(FILENAME, O_RDONLY, 0);
  if (fd < 0) {
    printf("No tasks file found or cannot be opened: %s\n", strerror(errno));
    return 0;
  }

  off_t file_size = lseekCheck(fd, 0, SEEK_END);
  int task_count = file_size / sizeof(Task);

  if (task_count == 0) {
    printf("No tasks found in file\n");
    closeCheck(fd);
    return 0;
  }

  printf("Found %d task(s) in file:\n\n", task_count);

  lseekCheck(fd, 0, SEEK_SET); // Go back to beginning
  Task task;
  int index = 0;

  for (int i = 0; i < task_count; i++) {
    readCheck(fd, &task, sizeof(Task));
    printf("Task #%d:\n", ++index);
    display_task(&task);
    printf("\n");
  }

  closeCheck(fd);
  return 1;
}

int print_help(void) {
  printf("Task Manager Commands:\n");
  printf("  c - Create new task\n");
  printf("  d - Display current task\n");
  printf("  s - Save current task to file\n");
  printf("  l - Load last task from file\n");
  printf("  a - List all tasks\n");
  printf("  h - Help\n");
  printf("  q - Quit\n");
  return 1;
}

int quit_program(void) {
  printf("Goodbye!\n");
  exit(0);
  return 1;
}

int display_current_task(void) {
  display_task(&current_task);
  return 1;
}

int save_current_task(void) { return save_task(&current_task); }

int load_current_task(void) { return load_task(&current_task); }

static const CommandOperation commands[] = {
    ['c'] = {read_task_from_stdin, "Create", "Create a new task"},
    ['d'] = {display_current_task, "Display", "Display current task"},
    ['s'] = {save_current_task, "Save", "Save task to file"},
    ['l'] = {load_current_task, "Load", "Load task from file"},
    ['a'] = {list_tasks, "List", "List all tasks"},
    ['h'] = {print_help, "Help", "Display help"},
    ['q'] = {quit_program, "Quit", "Exit the program"},
};

int main(void) {
  char choice;

  printf("-- Task Manager --\n");
  print_help();

  current_task = (Task){1, 1, 1, 1, 1};

  while (1) {
    printf("\nEnter command (h for help): ");
    scanf(" %c", &choice);

    if (choice >= 0 && choice < (int)sizeof(commands) / sizeof(commands[0]) &&
        commands[(int)choice].operation != NULL) {
      commands[(int)choice].operation();
    } else {
      printf("Unknown command: %c\n", choice);
      print_help();
    }
  }

  return 0;
}
