#include <stdlib.h>
#include "Encrypt.h"

int main (int argc, char** argv) {
    char *input = "test";
    char *output = (char *)malloc(sizeof(char) * (MD5_DIGEST_LENGTH * 2 + 1));
    
    hash_md5(input, output);

    printf("%s - %s\n", input, output);

    return 0;
}