#include "test.h"

void testPut() {
    char word[] = "ball";
    Node *root = createNode();

    put(root, word);

    assert(search(root, "ball"));
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
    assert(!search(root, "ball"));
    assert(search(root, "hello"));
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

