#include <assert.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

// Regex

int main(void) {
  {
    regex_t preg;
    int errcode = regcomp(&preg, "ab*", REG_ICASE | REG_EXTENDED);
    if (errcode != 0) {
      char error_message[100];
      regerror(errcode, &preg, error_message, sizeof(error_message));
      printf("Regex error: %s\n", error_message);
    }

    const char *string = "aBb";
    int result = regexec(&preg, string, 0, NULL, 0);

    if (result == 0)
      printf("match\n");
    else if (result == REG_NOMATCH)
      printf("no match\n");

    regfree(&preg);
  }
  printf("\n");
  {
    regex_t preg;
    int errcode = regcomp(&preg, "(ab*)(cd*)", REG_EXTENDED);
    if (errcode != 0) {
      char error_message[100];
      regerror(errcode, &preg, error_message, sizeof(error_message));
      printf("Regex error: %s\n", error_message);
    }

    const char *string = "##abbcddd##";
    const size_t nmatch = 10;
    regmatch_t pmatch[nmatch + 1];

    int result = regexec(&preg, string, nmatch, pmatch, 0);
    if (result == 0) {
      printf("match\n");
      for (size_t i = 0; pmatch[i].rm_so != -1 && i < nmatch; i++) {
        char buf[100] = {0};
        int start = pmatch[i].rm_so;
        int end = pmatch[i].rm_eo;
        strncpy(buf, string + start, end - start);
        printf("start: %d, end: %d: %s\n", start, end, buf);
      }
    } else if (result == REG_NOMATCH) {
      printf("no match\n");
    }

    regfree(&preg);
  }

  return 0;
}
