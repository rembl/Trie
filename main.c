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
    char ch;
    int n = 0;

    while (!feof(input_file)) {

        ch = (char) fgetc(input_file);
        char *single = (char*)malloc(sizeof(char));
        int m = 0;

        while(ch != '\n' && ch != ' ' && ch != EOF) {
            single[m] = ch;
            m++;
            single = (char*)realloc(single, sizeof(char) * (m + 1));
            ch = (char) fgetc(input_file);
        }

        words[n] = (char*)malloc(sizeof(char) * strlen(single));
        words[n] = single;
        n++;
        words = (char**)realloc(words, sizeof(char*) * (n + 1));
    }

    fclose(input_file);

    FILE *output_file = fopen(argv[2], "w");

    Node *root = createNode();
    for (int i = 0; i < n; i++) put(root, words[i]);

    delete(root, "23456");
    search(root, "23456");

    print(root, output_file);

    fclose(output_file);
    free(words);

    return 0;
}
