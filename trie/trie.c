/*
 * A simple implementation for trie (aka prefix tree) data structure.
 *
 * 2016 - Hoang Vuong <vuonghv.cs@gmail.com>
 */

#include "trie.h"
#include <stdlib.h>

static bool trie_isleaf(struct trie *node)
{
    if (!node)
        return false;

    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (node->next[i] != NULL)
            return false;
    }
    return true;
}

bool trie_insert(struct trie *root, const char *s)
{
    for (; *s; s++) {
        int i = CHAR_TO_INDEX(*s);
        if (!root->next[i]) {
            root->next[i] = (struct trie *)malloc(sizeof(struct trie));
            if (!root->next[i])
                return false;

            *root->next[i] = (struct trie) { .flag = 0 };
        }
        root = root->next[i];
    }
    root->flag |= TRIE_TERMINAL_FLAG;
    return true;
}

void trie_remove(struct trie *root, const char *s)
{
    struct trie *parent = NULL;
    int k;
    for (; *s; s++) {
        int i = CHAR_TO_INDEX(*s);
        if (!root->next[i])
            return;
        k = i;
        parent = root;
        root = root->next[i];
    }

    if (parent && trie_isleaf(root)) {
        free(root);
        parent->next[k] = NULL;
    } else {
        root->flag &= ~TRIE_TERMINAL_FLAG;
    }
}

bool trie_contains(struct trie *root, const char *s)
{
    for (; *s; s++) {
        int i = CHAR_TO_INDEX(*s);
        if (!root->next[i])
            return false;
        root = root->next[i];
    }

    if (root->flag & TRIE_TERMINAL_FLAG)
        return true;

    return false;
}

void trie_clear(struct trie *root)
{
    if (!root) return;

    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++)
        trie_clear(root->next[i]);

    free(root);
}

struct trie *trie_find(struct trie *root, const char *s)
{
    for (; *s; s++) {
        int i = CHAR_TO_INDEX(*s);
        if (!root->next[i])
            return NULL;
        root = root->next[i];
    }
    return root;
}

void trie_dfs_recursive(struct trie *root, char *buf, char *bufend,
                        trie_visitor v, void *arg)
{
    if (root->flag & TRIE_TERMINAL_FLAG) {
        *bufend = '\0';
        v(buf, arg);
    }

    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (root->next[i]) {
            *bufend = INDEX_TO_CHAR(i);
            trie_dfs_recursive(root->next[i], buf, bufend + 1, v, arg);
        }
    }
}

int trie_count(struct trie *root)
{
    int count = 0;

    if (root->flag & TRIE_TERMINAL_FLAG)
        ++count;

    for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
        if (root->next[i])
            count += trie_count(root->next[i]);
    }

    return count;
}

