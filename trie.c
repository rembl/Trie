#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

Node *createNode(void) {

    Node *new = (Node*)malloc(sizeof(Node));
    new->leaf = false;
    new->sibling = NULL;
    new->fChild = NULL;

    return new;
}

List *createList(void) {
    List *new = (List*)malloc(sizeof(List));
    new->rnNode = NULL;
    new->value = '\0';

    return new;
}

void put(Node *root, const char *word) {

    Node *current = createNode();
    current = root;

    if (word == NULL || strlen(word) == 0) return;

    for (int i = 0; i < (int) strlen(word); i++) {

        if (!current->fChild) {
            current->fChild = createList();
            current->fChild->rnNode = createNode();
            current->fChild->value = word[i];
        }

        Node *next = current->fChild->rnNode;

        while (current->fChild != NULL && current->fChild->value != word[i]) {
            if (next->sibling != NULL) next = next->sibling->rnNode ;
            else {
                next->sibling = createList();
                next->sibling->rnNode = createNode();
                next->sibling->value = word[i];
                next = next->sibling->rnNode;
            }
            current = next;
        }
        current = next;
    }

    current->leaf = true;
}

bool search(Node *root, const char *word) {

    Node *current = createNode();
    current = root;

    if (word == NULL || strlen(word) == 0) return false;

    for (int i = 0; i < (int) strlen(word); i++) {

        if (!current->fChild) {
            printf("Word '%s' not found :(\n", word);
            return false;
        }

        if (current->fChild->value != word[i]) {

            Node *next = current->fChild->rnNode;
            current = next;
            while (current->sibling != NULL && current->sibling->value != word[i]) {
                current = current->sibling->rnNode;
            }
            if (!current->sibling) {
                printf("Word '%s' not found :(\n", word);
                return false;
            }
            current = current->sibling->rnNode;
        }
        else current = current->fChild->rnNode;
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

    Node *current = createNode();
    current = root;
    Node *lastNode = createNode();
    char lastLetter = '\n';

    if (word == NULL || strlen(word) == 0) return;

    for (int i = 0; i < (int) strlen(word); i++) {

        if (!current->fChild) return;

        lastNode = current;

        if (current->fChild->value != word[i]) {

            Node *next = current->fChild->rnNode;
            current = next;
            while (current->sibling != NULL && current->sibling->value != word[i]) {
                current = current->sibling->rnNode;
               if (lastLetter == word[i-1]) {
                   lastLetter = '\n';
                   lastNode = lastNode->fChild->rnNode;
               } else lastNode = lastNode->sibling->rnNode;
            }
            if (!current->sibling) return;
            lastNode = lastNode->fChild->rnNode;
            current = current->sibling->rnNode;
        }
        else {
            lastLetter = current->fChild->value;
            current = current->fChild->rnNode;
        }

    }

    if (current->leaf && current->fChild) current->leaf = false;
    else if (current->leaf && !current->sibling) {
        free(lastNode->fChild->rnNode);
        lastNode->fChild = NULL;
    }
    else if (current->leaf && current->sibling) {
        free(lastNode->fChild->rnNode);
        lastNode->fChild = current->sibling;
    }
    else if (!current->leaf) return;

}

void print(Node* root, char printWord[], int letter, FILE *output_file) {

    Node *current = createNode();
    current = root;
    char currentLetter;

    if (current->fChild) {
        currentLetter = current->fChild->value;
        current = current->fChild->rnNode;
        recurse(current, currentLetter, printWord, letter, output_file);
    } else fputs("The trie is empty ;(", output_file);
    return;
}

void recurse(Node *current, char currentLetter, char *printWord, int letter, FILE *output_file) {

    // сосед
    if (current->sibling) recurse(current->sibling->rnNode, current->sibling->value, printWord, letter, output_file);

    // добавление буквы
    printWord[letter] = *(char*)malloc(sizeof(char));
    printWord[letter] = currentLetter;

    // конец
    if (current->leaf) {
        fputs(printWord, output_file);
        fputs("\n", output_file);
    }

    // ребенок
    if (current->fChild) {
        currentLetter = current->fChild->value;
        current = current->fChild->rnNode;
        recurse(current, currentLetter, printWord, letter + 1, output_file);
    }

    // удаление буквы
    printWord[letter] = ' ';
}
