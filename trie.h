#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET (26)

typedef struct Node
{
    struct Node *children[ALPHABET];
    bool leaf;
} Node;


Node *createNode(void);
void put(Node *root, const char *word);
bool search(Node *root, const char *word);
void delete(Node *root, const char *word);
int children(Node *root);
bool anyChildren(Node *root);
void print(Node* root, char printWord[], int letter, FILE *output_file);
