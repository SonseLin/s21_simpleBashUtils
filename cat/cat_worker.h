#ifndef CAT_WORKER_H
#define CAT_WORKER_H

#include <string.h>

#include "cat_processing.h"
#include "stdio.h"
#include "stdlib.h"

void cat(FILE *fptr, char *flag);
int valid_flag(char *flag);
void cat_with_flags(char *filename, char *flag);

#endif