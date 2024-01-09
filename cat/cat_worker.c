#include "cat_worker.h"

void cat_with_flags(char *filename, char *flag) {
  if (valid_flag(flag)) {
    FILE *fptr = fopen(filename, "r");
    if (fptr != NULL) {
      cat(fptr, flag);
      fclose(fptr);
    }
  }
}

void cat(FILE *fptr, char *flag) {
  int buffLength = 256;
  char buffer[buffLength];
  switch (flag[1]) {
    case 'n':
      cat_n(buffer, buffLength, fptr);
      break;
    case 'b':
      cat_b(buffer, buffLength, fptr);
      break;
    case 'e':
      cat_e(buffer, buffLength, fptr);
      break;
    case 's':
      cat_s(buffer, buffLength, fptr);
      break;
    case 't':
      cat_t(buffer, buffLength, fptr);
      break;
    default:
      cat_default(buffer, buffLength, fptr);
      break;
  }
}

int valid_flag(char *flag) {
  int res = 0;
  if (strcmp(flag, "--number-nonblank") == 0) {
    strcpy(flag, "-b");
  } else if (strcmp(flag, "-E") == 0) {
    strcpy(flag, "-e");
  } else if (strcmp(flag, "--number") == 0) {
    strcpy(flag, "-n");
  } else if (strcmp(flag, "--squeeze-blank") == 0) {
    strcpy(flag, "-s");
  } else if (strcmp(flag, "-T") == 0) {
    strcpy(flag, "-t");
  }
  if (strlen(flag) == 2) {
    res++;
    if (flag[0] == '-') res++;
    char f = flag[1];
    if (f == 'b' || f == 's' || f == 't' || f == 'e' || f == 'n') res++;
  } else if (strcmp(flag, "-default") == 0)
    res = 3;
  return res == 3;
}