#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

Node *createNode(void) {

    Node *current = (Node*)malloc(sizeof(Node));
    current->leaf = false;
    for (int i = 0; i < ALPHABET; i++) current->children[i] = NULL;

    return current;
}

void put(Node *root, const char *word) {
    Node *current = root;

    if(word == NULL || strlen(word) == 0) return;

    for (int i = 0; i < (int) strlen(word); i++) {
        int place = word[i] - 'a';
        if (!current->children[place]) current->children[place] = createNode();
        current = current->children[place];
    }

    current->leaf = true;
}

bool search(Node *root, const char *word) {
    Node *current = root;

    if(word == NULL || strlen(word) == 0) return false;

    for (int i = 0; i < (int) strlen(word); i++) {
        int place = word[i] - 'a';
        if (!current->children[place]) {
            printf("Word '%s' not found :(\n", word);
            return false;
        }
        current = current->children[place];
    }

    if (current->leaf) {
        printf("Word '%s' found :)\n", word);
        return true;
    }
    else {
        printf("Word '%s' not found :(\n", word);
        return false;
    }
}

void delete(Node *root, const char *word) {
    Node *current = root;
    Node *lastNode = createNode();
    int lastLetter = 0;

    if(word == NULL || strlen(word) == 0) return;

    for (int i = 0; i < (int) strlen(word); i++) {
        int place = word[i] - 'a';
        if (!current->children[place]) return;
        if (current->leaf || children(current) > 1) {
            lastNode = current;
            lastLetter = place;
        }
        current = current->children[place];
    }

    if (!current->leaf) return;
    if (anyChildren(current)) {
        current->leaf = false;
    } else {
        lastNode->children[lastLetter] = NULL;
    }

}

void print(Node* root, char printWord[], int letter, FILE *output_file) {
    if (root->leaf) {
        printWord[letter] = '\n';
        printWord[letter + 1] = '\0';
        fputs(printWord, output_file);
    }

    for (int i = 0; i < ALPHABET; i++) {
        if (root->children[i]) {
            printWord[letter] = i + 'a';
            print(root->children[i], printWord, letter + 1, output_file);
        }
    }
}

int children(Node *root) {
    int amount = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (root->children[i]) amount++;
    }
    return amount;
}

bool anyChildren(Node *root) {
    for (int i = 0; i < ALPHABET; i++)
        if (root->children[i])
            return true;
    return false;
}
