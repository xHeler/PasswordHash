#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **dictionary;
char **passwordsToBreak;
char **mailsToBreak;
int dictionaryLength;
int passwordToBreakLength;

void readFromFiles(const char *dictionaryFileName, const char *passwordsFileName);
void removeSpaces(char *str);
void separateStringBySpace(char *inputt, char **passwordToBreak, char **mailToBreak);