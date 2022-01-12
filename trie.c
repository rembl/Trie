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

void put(Node *current, const char *word) {

    if (word == NULL || strlen(word) == 0) return;

    for (int i = 0; i < (int) strlen(word); i++) {

        if (!current->fChild) {
            current->fChild = createList();
            current->fChild->rnNode = createNode();
            current->fChild->value = word[i];
        }

        Node *next = current->fChild->rnNode;

        if (current->fChild != NULL && current->fChild->value != word[i]) {
            while (next->sibling != NULL && next->sibling->value != word[i]) next = next->sibling->rnNode;
            if (next->sibling != NULL) next = next->sibling->rnNode;
            else {
                next->sibling = createList();
                next->sibling->rnNode = createNode();
                next->sibling->value = word[i];
                next = next->sibling->rnNode;
            }
        }
        current = next;
    }

    current->leaf = true;
}

bool search(Node *current, const char *word) {

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

void delete(Node *current, const char *word) {

    if (word == NULL || strlen(word) == 0) return;
    if (!search(current, word)) return;

    Node *root = current;
    Node *prevNode = createNode();
    int counter = 0;
    enum myLetter myl = YES;
    enum flag fl = PARENT;

    if (current->fChild->value != word[0]) {

        Node *next = current->fChild->rnNode;
        current = next;
        while (current->sibling->value != word[0]) {
            current = current->sibling->rnNode;
        }
        current = current->sibling->rnNode;
    }
    else current = current->fChild->rnNode;
    counter++;

    delrec(root, current, word, prevNode, fl, counter, myl);
    // myLetter - если 1, то мы в букве искомого слова, если 0 - нет
    // flag - если 1, то prevNode - родитель, елси 2, то prevNode - сосед
}

void delrec(Node *root, Node *current, const char *word, Node *prevNode, enum flag fl, int counter, enum myLetter myl) {

    //находим слово
    if (counter - (int) strlen(word) < 0) {
        if (myl == YES) {
            if (current->fChild->value == word[counter]) delrec(root, current->fChild->rnNode, word, current, PARENT, counter + 1, YES);
            else delrec(root, current->fChild->rnNode, word, current, PARENT, counter, NO);
        }
        else {
            while (current->sibling->value != word[counter]) {
                prevNode = current;
                current = current->sibling->rnNode;
            }
            delrec(root, current->sibling->rnNode, word, current, SIBLING, counter + 1, YES);
        }
    }

    //нет ребенка нет соседа
    if (current->fChild == NULL && current->sibling == NULL) {
        if (fl == PARENT) prevNode->fChild = NULL;
        else prevNode->sibling = NULL;
        free(current);
    }

    //нет ребенка есть сосед
    else if (current->fChild == NULL && current->sibling != NULL) {
        if (fl == PARENT) {
            if (prevNode->sibling == NULL && prevNode->fChild == NULL) root->fChild = current->sibling;
            else prevNode->fChild = current->sibling;
        }
        else prevNode->sibling = current->sibling;
        free(current);
    }

    //есть ребенок
    else if (current->fChild != NULL && counter == (int) strlen(word)) {
        if (fl == PARENT && prevNode->fChild->value == word[strlen(word) - 1]) current->leaf = false;
        if (fl == SIBLING && prevNode->sibling->value == word[strlen(word) - 1]) current->leaf = false;
    }
}

void print(Node* current, FILE *output_file) {

    char currentLetter;
    char *printWord = (char*)malloc(sizeof(char*));
    int letter = 0;

    if (current->fChild) {
        currentLetter = current->fChild->value;
        current = current->fChild->rnNode;
        recurse(current, currentLetter, printWord, letter, output_file);
    } else fputs("The trie is empty ;(", output_file);

    free(printWord);
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
