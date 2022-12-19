#include "Utils.h"
#include "Encrypt.h"

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

int compareStrings(char *str1, char *str2)
{
    int counter;
    if (sizeof(str1) < sizeof(str2))
    {
        counter = sizeof(str1);
    }
    else
    {
        counter = sizeof(str2);
    }
    for (int i = 0; i < counter; i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;
}

void removeNewLine(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != '\n')
            str[count++] = str[i];
    str[count] = '\0';
}

void checkPassword(char *password, int checkWithSpaces)
{
    int numberOfPasswords = 0;
    char md5[33]; // 32 characters + null
    if (checkWithSpaces == 0)
    {
        removeSpaces(password);
    }

    for (int k = 0; k < passwordToBreakLength; k++)
    {
        char *passwordToBreak = malloc(256);

        strcpy(passwordToBreak, passwordsToBreak[k]);

        hash_md5(password, md5);

        if (compareStrings(md5, passwordToBreak))
        {
            int isAlreadyExists = 0;

            for (int j = 0; j < numberOfPasswords; j++)
            {
                if (compareStrings(passwords[j], strdup(password)))
                {
                    alreadyExists = true;
                }
            }
            
            if (!alreadyExists)
            {
                (numberOfPasswords)++;
                passwords = realloc(passwords, (numberOfPasswords) * sizeof(char *));

                passwords[(numberOfPasswords)-1] = strdup(password);
                mails = realloc(mails, (numberOfPasswords) * sizeof(char *));
                mails[(numberOfPasswords)-1] = strdup(mailsToBreak[k]);
                newestPassword = strdup(password);
                newestMail = mails[(numberOfPasswords)-1];
                pthread_cond_signal(&cond);
            }
        }
        pthread_mutex_unlock(&mutex3);
    }
}