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

enum myLetter { YES, NO } myLetter;
enum flag { PARENT, SIBLING} flag;


Node *createNode(void);
void put(Node *root, const char *word);
bool search(Node *root, const char *word);
void delete(Node *root, const char *word);
void delrec(Node *root, Node *pNode, const char *word, Node *pNode1, enum flag, int counter, enum myLetter);
void print(Node* root, FILE *output_file);
void recurse(Node *current, char currentLetter, char *printWord, int letter, FILE *output_file);
