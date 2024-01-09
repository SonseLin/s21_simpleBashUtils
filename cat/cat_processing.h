#ifndef CAT_PROCESSING_H
#define CAT_PROCESSING_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void cat_default(char *buffer, int buffLength, FILE *fptr);
void cat_n(char *buffer, int buffLength, FILE *fptr);
void cat_b(char *buffer, int buffLength, FILE *fptr);
void cat_e(char *buffer, int buffLength, FILE *fptr);
void cat_s(char *buffer, int buffLength, FILE *fptr);
void cat_t(char *buffer, int buffLength, FILE *fptr);
char *replaceSubstring(char *original, char *substring, char *replacement);

#endif