#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Bad luck, wrong command line arguments");
        return 1;
    }

    char **words = (char**)malloc(sizeof(char*));
    FILE *input_file = fopen(argv[1], "r");
    int n = 0;
    int length = 0;

    while (!feof(input_file)) {
        words[n] = (char*)malloc(sizeof(char));
        fscanf(input_file, "%s", words[n]);
        if ((int) strlen(words[n]) > length) length = (int) strlen(words[n]);
        n++;
        words = (char**)realloc(words, sizeof(char*) * (n + 1));
    }
    fclose(input_file);

    FILE *output_file = fopen(argv[2], "w");
    char *printWord = (char*)malloc(length * sizeof(char*));

    Node *root = createNode();
    for (int i = 0; i < n; i++) put(root, words[i]);

    print(root, printWord, 0, output_file);

    fclose(output_file);
    free(words);
    free(printWord);

    return 0;
}
