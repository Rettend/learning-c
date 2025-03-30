#ifndef POSIX_UTILS_H
#define POSIX_UTILS_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern inline int open_check(const char *path, int flags, mode_t mode,
                             const char *file, int line) {
  int fd = open(path, flags, mode);
  if (fd < 0) {
    fprintf(stderr, "Error: Failed to open file '%s' at %s:%d\n", path, file,
            line);
    fprintf(stderr, "  Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return fd;
}

#define openCheck(path, flags, mode)                                           \
  open_check(path, flags, mode, __FILE__, __LINE__)

extern inline ssize_t read_check(int fd, void *buf, size_t count,
                                 const char *file, int line) {
  ssize_t result = read(fd, buf, count);
  if (result != (ssize_t)count) {
    fprintf(stderr, "Error: Read failed at %s:%d\n", file, line);
    fprintf(stderr, "  Expected: %zu bytes\n", count);
    fprintf(stderr, "  Actual: %zd bytes\n", result);
    if (result < 0) {
      fprintf(stderr, "  Error: %s\n", strerror(errno));
    }
    exit(EXIT_FAILURE);
  }
  return result;
}

#define readCheck(fd, buf, count) read_check(fd, buf, count, __FILE__, __LINE__)

extern inline ssize_t write_check(int fd, const void *buf, size_t count,
                                  const char *file, int line) {
  ssize_t result = write(fd, buf, count);
  if (result != (ssize_t)count) {
    fprintf(stderr, "Error: Write failed at %s:%d\n", file, line);
    fprintf(stderr, "  Expected: %zu bytes\n", count);
    fprintf(stderr, "  Actual: %zd bytes\n", result);
    if (result < 0) {
      fprintf(stderr, "  Error: %s\n", strerror(errno));
    }
    exit(EXIT_FAILURE);
  }
  return result;
}

#define writeCheck(fd, buf, count)                                             \
  write_check(fd, buf, count, __FILE__, __LINE__)

extern inline off_t lseek_check(int fd, off_t offset, int whence,
                                const char *file, int line) {
  off_t result = lseek(fd, offset, whence);
  if (result == (off_t)-1) {
    fprintf(stderr, "Error: lseek failed at %s:%d\n", file, line);
    fprintf(stderr, "  Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return result;
}

#define lseekCheck(fd, offset, whence)                                         \
  lseek_check(fd, offset, whence, __FILE__, __LINE__)

extern inline int close_check(int fd, const char *file, int line) {
  int result = close(fd);
  if (result != 0) {
    fprintf(stderr, "Error: Failed to close file descriptor at %s:%d\n", file,
            line);
    fprintf(stderr, "  Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return result;
}

#define closeCheck(fd) close_check(fd, __FILE__, __LINE__)

#endif // POSIX_UTILS_H
