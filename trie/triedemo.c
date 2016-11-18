/*
 * Trie data structure demo
 *
 * Compile: gcc -std=c99 -o triedemo triedemo.c trie.c
 */

#include "trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_KEY_LENGTH 30

void print_key(const char *key, void *arg) {
    printf("%s\n", key);
}

int main(int argc, char *argv[])
{
    struct trie *root = (struct trie *)malloc(sizeof(struct trie));
    *root = (struct trie) { .flag = 0 };
    char buf[MAX_KEY_LENGTH];

    char *keys[] = { "HAHA", "HOHO", "GOOD", "GOOGLE", "GO", NULL };

    for (int i = 0; keys[i]; i++)
        trie_insert(root, keys[i]);

    printf("All keys:\n");
    trie_dfs_recursive(root, buf, buf, print_key, NULL);

    // Assert all keys
    assert(trie_count(root) == 5);
    for (int i = 0; keys[i]; i++)
        assert(trie_contains(root, keys[i]));

    assert(!trie_contains(root, "JAMES"));

    struct trie *child = trie_find(root, "GO");
    assert(trie_contains(child, "OD"));
    assert(trie_contains(child, "OGLE"));
    printf("Number of keys beginning with \"GO\": %d\n", trie_count(child));

    trie_remove(root, "GO");
    trie_remove(root, "HAHA");

    assert(!trie_contains(root, "GO"));
    assert(!trie_contains(root, "HAHA"));
    assert(trie_contains(root, "HOHO"));
    assert(trie_contains(root, "GOOGLE"));
    assert(trie_contains(root, "GOOD"));

    trie_clear(root);
    return 0;
}

