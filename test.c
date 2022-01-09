#include "test.h"

void testPut() {
    char word[] = "bal";
    char word2[] = "he";
    Node *root = createNode();

    put(root, word);
    put(root, word2);

    assert(search(root, "he"));
    assert(search(root, "bal"));
    assert(!search(root, "balls"));
}

void testSearch() {
    char word[] = "ball";
    Node *root = createNode();

    put(root, word);

    assert(search(root, "ball"));
    assert(!search(root, "ba"));
}

void testDelete() {
    char word1[] = "ball";
    char word2[] = "hello";
    Node *root = createNode();

    put(root, word1);
    put(root, word2);

    assert(search(root, "ball"));
    assert(search(root, "hello"));
    delete(root, "ball");
    assert(search(root, "hello"));
    assert(!search(root, "ball"));
}

void testAll() {
    testPut();
    testSearch();
    testDelete();
}

int main() {
    testAll();

    return 0;
}

