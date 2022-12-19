#include <stdlib.h>
#include "Encrypt.h"
#include "Utils.h"

int main (int argc, char** argv) {
    if (argc != 3) return -1;

    char *input = "test";
    char *output = (char *)malloc(sizeof(char) * (MD5_DIGEST_LENGTH * 2 + 1));
    
    hash_md5(input, output);

    printf("%s - %s\n", input, output);

    readFromFiles(argv[1], argv[2]);

    for (int i = 0; i < passwordToBreakLength; i++) {
        printf("%d. %s \n", i, passwordsToBreak[i]);
    }

    return 0;
}