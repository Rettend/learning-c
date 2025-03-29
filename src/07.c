#include <stdbool.h>
#include <stdio.h>

// Tagged unions

enum Tag {
  TAG_BOOL,
  TAG_INT,
  TAG_FLOAT,
};

typedef struct {
  enum Tag tag;
  union {
    bool b;
    int i;
    float f;
  };
} Dynamic;

static const char *b(bool val) { return val ? "true" : "false"; }

int main(void) {
  Dynamic d = {.tag = TAG_FLOAT, .f = 2.3};

  switch (d.tag) {
  case TAG_BOOL:
    printf("bool: %s\n", b(d.b));
    break;
  case TAG_INT:
    printf("int: %d\n", d.i);
    break;
  case TAG_FLOAT:
    printf("float: %f\n", d.f);
    break;
  }

  return 0;
}
