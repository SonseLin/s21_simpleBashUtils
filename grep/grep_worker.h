#ifndef GREP_WORKER_H
#define GREP_WORKER_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
typedef int bool;

typedef struct parameters {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
  bool success;
} parameters;

void paramsInit(parameters* param);
void deleteLast(char* s);

bool insertParameter(char flag, parameters* p);
void writeToFile(int argc, char** argv, int i, int j, FILE* file);
void print_error_message(char** argv, int i, int j);
bool checkFlags(int argc, char** argv, parameters* params);
void createTempFile();
bool fillPatternsFromFiles();
void fillFiles(int argc, char** argv);
void printLine(parameters* params, int quantityOfFiles, char* path, char* line,
               int lineCounter);
void grep(parameters* params, int quantityOfFiles, int quantityOfPatterns);
int countFiles();
int countPatterns();
void magic();

#endif