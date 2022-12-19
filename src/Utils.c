#include "Utils.h"

void readFromFiles(const char *dictionaryFileName, const char *passwordsFileName)
{
    dictionaryLength = 0;
    passwordToBreakLength = 0;

    FILE *dictionaryFile = fopen(dictionaryFileName, "r");
    if (dictionaryFile == NULL)
    {
        printf("Failed to open the file: %s\n", dictionaryFileName);
        return;
    }
    // Read the file line by line
    char *line = malloc(33);
    char passwordLine[256];

    while (fgets(line, 2 * sizeof(char *), dictionaryFile))
    {
        dictionaryLength++;
        dictionary = realloc(dictionary, dictionaryLength * sizeof(char *));

        removeSpaces(line);
        dictionary[dictionaryLength - 1] = strdup(line);
    }

    FILE *passwordFile = fopen(passwordsFileName, "r");
    while (fgets(passwordLine, sizeof(passwordLine), passwordFile))
    {

        passwordToBreakLength++;
        passwordsToBreak = realloc(passwordsToBreak, passwordToBreakLength * sizeof(char *));
        mailsToBreak = realloc(mailsToBreak, passwordToBreakLength * sizeof(char *));
        separateStringBySpace(passwordLine, &passwordsToBreak[passwordToBreakLength - 1], &mailsToBreak[passwordToBreakLength - 1]);
    }

    fclose(dictionaryFile);
    fclose(passwordFile);
}

void removeSpaces(char *str)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
            str[count++] = str[i];
    str[count] = '\0';
}

void separateStringBySpace(char *inputt, char **passwordToBreak, char **mailToBreak)
{
    char *input = malloc(256);
    strncpy(input, inputt, 256);
    char *token = strtok(input, " ");

    int counter = 0;
    while (token != NULL)
    {
        removeSpaces(token);

        if (counter == 1)
        {
            *passwordToBreak = token;
        }
        if (counter == 2)
        {
            *mailToBreak = token;
        }
        token = strtok(NULL, " ");
        counter++;
    }
}