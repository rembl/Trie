#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    struct List *fChild;
    struct List *sibling;
    bool leaf;
} Node;

typedef struct List {
    char value;
    struct Node *rnNode;
} List;


Node *createNode(void);
void put(Node *root, const char *word);
bool search(Node *root, const char *word);
void delete(Node *root, const char *word);
void print(Node* root, char printWord[], int letter, FILE *output_file);
