#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **passwordsFound;
char **dictionary;
char **passwordsToBreak;
char **mailsToBreak;
int dictionaryLength;
int passwordToBreakLength;
int numberOfPasswordsFound;

void readFromFiles(const char *dictionaryFileName, const char *passwordsFileName);
void removeSpaces(char *str);
void separateStringBySpace(char *inputt, char **passwordToBreak, char **mailToBreak);
int compareStrings(char *str1, char *str2);
void removeNewLine(char *str);

void checkPassword(char *password, int checkWithSpaces);