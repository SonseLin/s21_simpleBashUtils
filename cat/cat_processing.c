#include "cat_processing.h"

void cat_default(char *buffer, int buffLength, FILE *fptr) {
  while (fgets(buffer, buffLength, fptr)) {
    printf("%s", buffer);
  }
}

void cat_n(char *buffer, int buffLength, FILE *fptr) {
  int counter = 1;
  while (fgets(buffer, buffLength, fptr)) {
    printf("%6d", counter++);
    printf("\t%s", buffer);
  }
}

void cat_b(char *buffer, int buffLength, FILE *fptr) {
  int counter = 1;
  while (fgets(buffer, buffLength, fptr)) {
    if (buffer[0] != '\n') printf("%6d%s", counter++, buffer);
  }
}

void cat_e(char *buffer, int buffLength, FILE *fptr) {
  while (fgets(buffer, buffLength, fptr)) {
    if (buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '$';
      printf("%s\n", buffer);
    } else
      printf("%s", buffer);
  }
}

void cat_s(char *buffer, int buffLength, FILE *fptr) {
  size_t print_blank = 0;
  while (fgets(buffer, buffLength, fptr)) {
    if (strlen(buffer) == 1 && buffer[0] == '\n')
      print_blank = 1;
    else {
      if (print_blank) {
        printf("\n");
        print_blank = 0;
      }
      printf("%s", buffer);
    }
  }
}

void cat_t(char *buffer, int buffLength, FILE *fptr) {
  while (fgets(buffer, buffLength, fptr)) {
    char *new = replaceSubstring(buffer, "\t", "^I");
    if (new != NULL) {
      printf("%s", new);
      free(new);
    }
  }
}

char *replaceSubstring(char *original, char *substring, char *replacement) {
  size_t len = strlen(original);
  size_t substrLen = strlen(substring);
  size_t replLen = strlen(replacement);
  if (substrLen / replLen > 1) {
    len *= substrLen / replLen;
  } else {
    len *= 2;
  }

  char *newStr = malloc(len * sizeof(char));
  if (newStr == NULL) {
    printf("Memory allocation failed.\n");
    return NULL;
  }

  int counter = 0;
  char *ptr = original;

  while (*ptr != '\0') {
    if (*ptr != *substring) {
      newStr[counter++] = *ptr;
      ptr++;
    } else {
      char *tmp = ptr;
      char *tmp_sub = substring;
      while (*tmp != '\0' && *tmp_sub != '\0' && *tmp == *tmp_sub) {
        tmp++;
        tmp_sub++;
      }
      if (*tmp_sub == '\0') {
        for (char *ptr_sub = replacement; *ptr_sub != '\0'; ptr_sub++) {
          newStr[counter++] = *ptr_sub;
        }
        ptr += substrLen;
      } else {
        newStr[counter++] = *ptr;
        ptr++;
      }
    }
  }
  newStr[counter] = '\0';
  return newStr;
}