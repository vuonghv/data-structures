/*
 * Implementation for Binary Search Tree
 *
 * 2016 - Vuong Hoang <vuonghv.cs@gmail.com>
 */

#ifndef _BST_H
#define _BST_H

struct bst {
    int key;
    struct bst *parent;
    struct bst *left;
    struct bst *right;
};

struct bst *bst_search(struct bst *root, int key);
struct bst *bst_insert(struct bst *root, int key);
void bst_delete(struct bst *root, int key);

/*
 * Return the node whose smallest key
 */
struct bst *bst_min(struct bst *root);

/*
 * Return the node whose largest key
 */
struct bst *bst_max(struct bst *root);

/*
 * Return the node whose smallest key that greater than the input key
 */
struct bst *bst_successor(struct bst *node);

/*
 * Return the node whose largest key that less than the input key
 */
struct bst *bst_predcessor(struct bst *node);

void bst_destroy(struct bst *root);

#endif
