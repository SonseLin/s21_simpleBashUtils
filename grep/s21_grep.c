#include "grep_worker.h"

int main(int argc, char* argv[]) {
  parameters* params = malloc(sizeof(parameters) * 2);
  paramsInit(params);
  createTempFile();
  if (!checkFlags(argc, argv, params)) {
    deleteGarbage();
    return 0;
  }
  fillFiles(argc, argv);
  if (params->f == true) {
    if (fillPatternsFromFiles() == false) {
      deleteGarbage();
      return 0;
    }
  }
  if (params->f == false && params->e == false) {
    magic();
  }
  int files = countFiles();
  int patterns = countPatterns();
  grep(params, files, patterns);
  return 0;
}