/*
 * 2016 - Vuong Hoang <vuonghv.cs@gmail.com>
 *
 * To compile: gcc -std=c99 -o testbst testbst.c bst.c
 */

#include "bst.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define BST_DELETE bst_delete

bool is_bst(struct bst *root)
{
    if (!root)
        return true;

    if (root->left && root->left->key >= root->key)
        return false;

    if (root->right && root->right->key <= root->key)
        return false;

    return is_bst(root->left) && is_bst(root->right);
}

void print_preorder(struct bst *root)
{
    if (!root)
        return;
    print_preorder(root->left);
    printf("%-4d", root->key);
    print_preorder(root->right);
}

int main(void)
{
    int arr[] = { 40, 30, 65, 25, 35, 50, 10, 28, 33, 34 };
    int arr_len = sizeof(arr)/sizeof(arr[0]);

    struct bst *root = NULL; // Must set root to NULL
    for (int i = 0; i < arr_len; i++)
        root = bst_insert(root, arr[i]);

    print_preorder(root);
    printf("\n");
    assert(is_bst(root));

    printf("TEST: BST search\n");
    for (int i = 0; i < arr_len; i++)
        assert(bst_search(root, arr[i]) != NULL);

    printf("TEST: BST min/max\n");
    struct bst *min_node = bst_min(root);
    struct bst *max_node = bst_max(root);
    assert(min_node->key == 10); 
    assert(max_node->key == 65);

    printf("TEST: BST successor/predcessor\n");
    assert(bst_successor(max_node) == NULL);
    assert(bst_predcessor(min_node) == NULL);

    struct bst *node = bst_search(root, 33);
    assert(bst_successor(node)->key == 34);
    assert(bst_predcessor(node)->key == 30);

    node = bst_search(root, 28);
    assert(bst_successor(node)->key == 30);
    assert(bst_predcessor(node)->key == 25);

    node = bst_search(root, 40);
    assert(bst_successor(node)->key == 50);
    assert(bst_predcessor(node)->key == 35);

    printf("TEST: BST delete\n");
    printf("---Original--: ");
    print_preorder(root);
    printf("\n");

    root = BST_DELETE(root, 30);
    assert(is_bst(root));
    assert(bst_search(root, 30) == NULL);
    printf("[*] delete %d: ", 30);
    print_preorder(root);
    printf("\n");

    root = BST_DELETE(root, 35);
    assert(is_bst(root));
    assert(bst_search(root, 35) == NULL);
    printf("[*] delete %d: ", 35);
    print_preorder(root);
    printf("\n");

    // Test delete root
    root = BST_DELETE(root, 40);
    assert(is_bst(root));
    assert(bst_search(root, 40) == NULL);
    printf("[*] delete %d: ", 40);
    print_preorder(root);
    printf("\n");

    printf("YEAH! ALL TESTS PASS!\n");
    bst_destroy(root);
    return 0;
}

