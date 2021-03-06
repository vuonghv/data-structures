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

struct bst *bst_insert_recursive(struct bst *root, int key)
{
    if (!root)
        return make_node(key);

    if (key < root->key) {
        root->left = bst_insert_recursive(root->left, key);
        root->left->parent = root;
    } else if (key > root->key) {
        root->right = bst_insert_recursive(root->right, key);
        root->right->parent = root;
    }

    return root;
}

struct bst *bst_insert(struct bst *root, int key)
{
    if (!root)
        return make_node(key);

    struct bst *parent = root;
    struct bst *child = root;

    while (child && key != child->key) {
        if (key < child->key) {
            parent = child;
            child = parent->left;
        } else if (key > child->key) {
            parent = child;
            child = parent->right;
        }
    }

    if (!child) {
        struct bst *new_node = make_node(key);
        new_node->parent = parent;

        if (key < parent->key)
            parent->left = new_node;
        else if (key > parent->key)
            parent->right = new_node;
    }

    return root;
}

static inline void replace_child_node(struct bst *old, struct bst *new)
{
    if (old->parent) {
        if (old->parent->left == old)
            old->parent->left = new;
        else
            old->parent->right = new;
    }

    if (new)
        new->parent = old->parent;
}

struct bst *bst_delete(struct bst *root, int key)
{
    struct bst *del_node = bst_search(root, key);

    if (!del_node)
        return root;

    struct bst *replace_node;

    if (!del_node->left && !del_node->right) {
        // leaf node
        replace_child_node(del_node, NULL);
        replace_node = NULL;

    } else if (del_node->left && del_node->right) {
        struct bst *successor = bst_successor(del_node);
        replace_child_node(successor, successor->right);
        replace_node = del_node;
        replace_node->key = successor->key; // Move successor to node, reserve children
        del_node = successor; // Delete old successor

    } else if (del_node->left) {
        // node only have left child
        replace_child_node(del_node, del_node->left);
        replace_node = del_node->left;

    } else {
        // finnally, node only have right child
        replace_child_node(del_node, del_node->right);
        replace_node = del_node->right;
    }

    if (del_node == root)
        root = replace_node;

    free(del_node);
    return root;
}

struct bst *bst_delete_recursive(struct bst *root, int key)
{
    if (!root)
        return NULL;

    if (key < root->key)
        root->left = bst_delete_recursive(root->left, key);
    else if (key > root->key)
        root->right = bst_delete_recursive(root->right, key);
    else { // Found key
        struct bst *tmp = root;
        if (root->left && root->right) {
            // Has 2 childs
            tmp = bst_min(root->right);
            root->key = tmp->key;
            root->right = bst_delete_recursive(root->right, root->key);
        } else {
            // Has 1 or 0 child
            if (root->left)
                root = root->left;
            else if (root->right)
                root = root->right;
            else
                root = NULL;

            free(tmp);
        }
    }

    return root;
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

