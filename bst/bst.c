/*
 * Implementation for Binary Search Tree
 *
 * 2016 - Vuong Hoang <vuonghv.cs@gmail.com>
 */

#include "bst.h"
#include <stdlib.h>

static struct bst *make_node(int key)
{
    struct bst *node = (struct bst *)malloc(sizeof(struct bst));
    if (node) {
        //*node = (struct bst) { .key = key };
        node->key = key;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct bst *bst_search_recursive(struct bst *root, int key)
{
    if (!root)
        return NULL;
    if (root->key == key)
        return root;
    else if (key < root->key)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}

struct bst *bst_search(struct bst *root, int key)
{
    while (root && root->key != key) {
        if (root->key > key)
            root = root->left;
        else
            root = root->right;
    }

    return root;
}

struct bst *bst_insert(struct bst *root, int key)
{
    if (!root)
        return make_node(key);

    if (key < root->key) {
        root->left = bst_insert(root->left, key);
        root->left->parent = root;
    } else if (key > root->key) {
        root->right = bst_insert(root->right, key);
        root->right->parent = root;
    }

    return root;
}

static inline void replace_node(struct bst *old, struct bst *new)
{
    if (old->parent->left == old)
        old->parent->left = new;
    else
        old->parent->right = new;

    if (new)
        new->parent = old->parent;
}

void bst_delete(struct bst *root, int key)
{
    struct bst *node = bst_search(root, key);

    if (!node)
        return;

    // leaf node
    if (!node->left && !node->right) {
        replace_node(node, NULL);
    } else if (node->left && node->right) {
        struct bst *successor = bst_successor(node);
        replace_node(successor, successor->right);
        replace_node(node, successor);
    } else if (node->left) {
        replace_node(node, node->left);
    } else {
        replace_node(node, node->right);
    }

    free(node);
}

void bst_destroy(struct bst *root)
{
    if (!root) {
        return;
    }

    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
}

struct bst *bst_min(struct bst *root)
{
    if (!root)
        return NULL;

    while (root->left)
        root = root->left;

    return root;
}
    
struct bst *bst_max(struct bst *root)
{
    if (!root)
        return NULL;

    while (root->right)
        root = root->right;

    return root;
}

struct bst *bst_successor(struct bst *node)
{
    if (node->right)
        return bst_min(node->right);

    while (node->parent && node->parent->left != node)
        node = node->parent;

    return node->parent;
}

struct bst *bst_predcessor(struct bst *node)
{
    if (node->left)
        return bst_max(node->left);

    while (node->parent && node->parent->right != node)
        node = node->parent;

    return node->parent;
}

