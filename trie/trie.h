/*
 * A simple implementation for trie (aka prefix tree) data structure
 *
 * The current implementation support insert/remove/search keys that includes
 * 26 upper English character (A -> Z).
 *
 * To support keys with more than 26 characters (e.g 256 ASCII characters),
 * you just need to redefine TRIE_ALPHABET_SIZE, CHAR_TO_INDEX, INDEX_TO_CHAR
 * macros.
 * E.g For keys with 256 ASCII characters:
 *      #define TRIE_ALPHABET_SIZE 256
 *      #define CHAR_TO_INDEX(c) (c)
 *      #define INDEX_TO_CHAR(i) (i)
 *
 * 2016 - Hoang Vuong <vuonghv.cs@gmail.com>
 */

#ifndef _TRIE_H
#define _TRIE_H

#include <stdbool.h>

#define TRIE_ALPHABET_SIZE 26
#define TRIE_TERMINAL_FLAG (1 << 0)

#define CHAR_TO_INDEX(c) (c - 'A')
#define INDEX_TO_CHAR(i) (i + 'A')

struct trie {
    int flag;
    struct trie *next[TRIE_ALPHABET_SIZE];
};

bool trie_insert(struct trie *root, const char *s);
void trie_remove(struct trie *root, const char *s);
bool trie_contains(struct trie *root, const char *s);
void trie_clear(struct trie *root);
struct trie *trie_find(struct trie *root, const char *s);

typedef void (*trie_visitor)(const char *key, void *arg);
void trie_dfs_recursive(struct trie *root, char *buf, char *bufend,
                        trie_visitor v, void *arg);

int trie_count(struct trie *root);

#endif

