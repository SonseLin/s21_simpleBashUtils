#include "grep_worker.h"

bool insertParameter(char flag, parameters* params) {
  switch (flag) {
    case 'e':
      params->e = true;
      break;
    case 'i':
      params->i = true;
      break;
    case 'v':
      params->v = true;
      break;
    case 'c':
      params->c = true;
      break;
    case 'l':
      params->l = true;
      break;
    case 'n':
      params->n = true;
      break;
    case 'h':
      params->h = true;
      break;
    case 's':
      params->s = true;
      break;
    case 'f':
      params->f = true;
      break;
    case 'o':
      params->o = true;
      break;
    default:
      params->success = false;
      break;
  }
  return params->success;
}

void writeToFile(int argc, char** argv, int i, int j, FILE* file) {
  if (j < (int)strlen(argv[i]) - 1) {
    for (j++; j < (int)strlen(argv[i]); j++) {
      fprintf(file, "%c", argv[i][j]);
    }
    fprintf(file, "\n");
  } else {
    if (i < argc - 1) {
      fprintf(file, "%s\n", argv[i + 1]);
      i++;
    }
  }
}

void print_error_message(char** argv, int i, int j) {
  printf("grep: invalid option -- %c\n", argv[i][j]);
  printf(
      "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
      "[-C[num]]\n");
  printf(
      "        [-e pattern] [-f file] [--binary-files=value] "
      "[--color=when]\n");
  printf(
      "        [--context[=num]] [--directories=action] [--label] "
      "[--line-buffered]\n");
  printf("        [--null] [pattern] [file ...]\n");
}

bool checkFlags(int argc, char** argv, parameters* params) {
  FILE* patternFiles = fopen(".patternFiles", "a");
  FILE* patterns = fopen(".patterns", "a");
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; j < (int)strlen(argv[i]) && params->success; j++) {
        if (argv[i][j] == 'e' || argv[i][j] == 'f') {
          if (argv[i][j] == 'e') {
            writeToFile(argc, argv, i, j, patterns);
            params->e = true;
          } else {
            writeToFile(argc, argv, i, j, patternFiles);
            params->f = true;
          }
          break;
        } else if (!insertParameter(argv[i][j], params)) {
          print_error_message(argv, i, j);
        }
      }
    }
  }
  fclose(patterns);
  fclose(patternFiles);
  return params->success;
}

void createTempFile() {
  FILE* patternFiles = fopen(".patternFiles", "w");
  FILE* patterns = fopen(".patterns", "w");
  FILE* words = fopen(".files", "w");
  fclose(patternFiles);
  fclose(patterns);
  fclose(words);
}

bool fillPatternsFromFiles() {
  FILE* patternFiles = fopen(".patternFiles", "r");
  FILE* patterns = fopen(".patterns", "a");
  char path[1024];
  while (fgets(path, 1024, patternFiles)) {
    deleteLast(path);
    FILE* file = fopen(path, "r");
    if (file == NULL) {
      printf("grep: %s: No such file or directory\n", path);
      fclose(patternFiles);
      fclose(patterns);
      return 0;
    }
    char pattern[1024];
    while (fgets(pattern, 1024, file)) {
      fprintf(patterns, "%s", pattern);
    }
    fclose(file);
  }
  fclose(patternFiles);
  fclose(patterns);
  return 1;
}

void fillFiles(int argc, char** argv) {
  FILE* files = fopen(".files", "a");
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (argv[i - 1][0] == '-') {
        int len = (int)strlen(argv[i - 1]);
        if (argv[i - 1][len - 1] != 'f' && argv[i - 1][len - 1] != 'e') {
          fprintf(files, "%s\n", argv[i]);
        }
      } else {
        fprintf(files, "%s\n", argv[i]);
      }
    }
  }
  fclose(files);
}

void printLine(parameters* params, int quantityOfFiles, char* path, char* line,
               int lineCounter) {
  if (params->l == false && params->c == false) {
    if (params->h == false && quantityOfFiles != 1) {
      printf("%s:", path);
    }
    if (params->n == true) {
      printf("%d:", lineCounter);
    }
    printf("%s", line);
  }
}

void grep(parameters* params, int quantityOfFiles, int quantityOfPatterns) {
  FILE* patterns = fopen(".patterns", "r");
  FILE* files = fopen(".files", "r");
  char pattern[1024];
  char path[1024];
  regex_t* regex = malloc(quantityOfPatterns * sizeof(regex_t));
  int flag = 0;
  if (params->i == true) {
    flag = REG_ICASE;
  }
  int counter = 0;
  while (fgets(pattern, 1024, patterns)) {
    deleteLast(pattern);
    regcomp(&regex[counter++], pattern, flag);
  }
  fclose(patterns);
  while (fgets(path, 1024, files)) {
    deleteLast(path);
    FILE* file = fopen(path, "r");
    if (file == NULL) {
      if (!params->s) {
        printf("grep: %s: No such file or directory\n", path);
      }
      continue;
    }
    char line[1024];
    int lineCounter = 0;
    int matchCounter = 0;
    bool fileFlag = false;
    while (fgets(line, 1024, file)) {
      lineCounter++;
      regmatch_t find;
      for (int i = 0; i < quantityOfPatterns; i++) {
        int returnValue = regexec(&regex[i], line, 0, &find, 0);
        if (params->v == true && returnValue == REG_NOMATCH) {
          printLine(params, quantityOfFiles, path, line, lineCounter);
          matchCounter++;
          if (params->l) {
            fileFlag = true;
          }
          break;
        }
        if (!params->v && returnValue == 0) {
          printLine(params, quantityOfFiles, path, line, lineCounter);
          matchCounter++;
          if (params->l) {
            fileFlag = true;
          }
          break;
        }
      }
      if (fileFlag) {
        break;
      }
    }
    if (params->c) {
      if (!params->h && quantityOfFiles != 1) {
        printf("%s:", path);
      }
      printf("%d\n", matchCounter);
    }
    if (params->l && matchCounter != 0) {
      printf("%s\n", path);
    }
    fclose(file);
  }
  for (int i = 0; i < quantityOfPatterns; i++) {
    regfree(&regex[i]);
  }
  free(regex);
  fclose(files);
}

int countFiles() {
  FILE* files = fopen(".files", "r");
  int answer = 0;
  char file[1024];
  while (fgets(file, 1024, files)) {
    answer++;
  }
  return answer;
}

int countPatterns() {
  FILE* patterns = fopen(".patterns", "r");
  int answer = 0;
  char pattern[1024];
  while (fgets(pattern, 1024, patterns)) {
    answer++;
  }
  return answer;
}

void magic() {
  FILE* files = fopen(".files", "r");
  FILE* patterns = fopen(".patterns", "a");
  FILE* secondFiles = fopen(".secondFiles", "w");
  char file[1024];
  char* lastCall = fgets(file, 1024, files);
  fprintf(patterns, "%s", file);
  lastCall = fgets(file, 1024, files);
  while (lastCall) {
    fprintf(secondFiles, "%s", file);
    lastCall = fgets(file, 1024, files);
  }
  fclose(secondFiles);
  fclose(patterns);
  fclose(files);
  files = fopen(".files", "w");
  secondFiles = fopen(".secondFiles", "r");
  while (fgets(file, 1024, secondFiles)) {
    fprintf(files, "%s", file);
  }
  fclose(files);
  fclose(secondFiles);
}

void deleteLast(char* s) {
  int len = strlen(s);
  if (len > 1) {
    s[len - 1] = '\0';
  }
}

void paramsInit(parameters* param) {
  param->e = false;
  param->i = false;
  param->v = false;
  param->c = false;
  param->l = false;
  param->n = false;
  param->h = false;
  param->s = false;
  param->f = false;
  param->o = false;
  param->success = true;
}