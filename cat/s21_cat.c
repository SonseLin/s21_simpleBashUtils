#include <string.h>

#include "cat_worker.h"

int main(int argc, char **argv) {
  int any_err = 1;
  if (argc >= 2) {
    if (valid_flag(argv[1])) {
      for (int i = 2; i < argc; i++) {
        cat_with_flags(argv[i], argv[1]);
        any_err = 0;
      }
    } else {
      for (int i = 1; i < argc; i++) {
        cat_with_flags(argv[i], "-default");
        any_err = 0;
      }
    }
  }
  if (any_err) printf("incorrect input");
  return 0;
}