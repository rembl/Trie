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
void delrec(Node *pNode, const char *word, Node *pNode1, int i, int counter, int myLetter);
void print(Node* root, FILE *output_file);
void recurse(Node *current, char currentLetter, char *printWord, int letter, FILE *output_file);
