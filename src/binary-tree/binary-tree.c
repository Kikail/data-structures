//
// Created by killi on 31/10/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "binary-tree.h"

struct BinaryTreeNode* BinaryTreeNode_CreateEmpty(void* parent, void* data, void* key) {
    struct BinaryTreeNode* node = malloc(sizeof(struct BinaryTreeNode));
    node->data = data;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}
BinaryTree* BinaryTree_CreateEmpty(int(*compareFunction)(void*, void*)) {
    if(!compareFunction) return NULL;
    BinaryTree* tree = malloc(sizeof(struct BinaryTree));
    tree->root = NULL;
    tree->compareFunction = compareFunction;
    tree->size = 0;
    return tree;
}

bool BinaryTreeNode_Put(struct BinaryTreeNode* tree_node, void* data, void* key, int(*compareFunction)(void*, void*)) {
    if(!tree_node || !data || !key || !compareFunction) return false;
    int cmp = compareFunction(key, tree_node->key);
    if (cmp == 0) {
        tree_node->data = data;
        return false;
    }
    if (cmp < 0) {
        if (tree_node->left) return BinaryTreeNode_Put(tree_node->left, data, key, compareFunction);
        else {
            tree_node->left = BinaryTreeNode_CreateEmpty(tree_node, data, key);
            return true;
        }
    }
    else {
        if (tree_node->right) return BinaryTreeNode_Put(tree_node->right, data, key, compareFunction);
        else {
            tree_node->right = BinaryTreeNode_CreateEmpty(tree_node, data, key);
            return true;
        }
    }
}

void BinaryTree_Put(BinaryTree* tree, void* data, void* key) {
    if(!tree || !data || !key) return;
    bool add_size = true;
    if(tree->root == NULL) tree->root = BinaryTreeNode_CreateEmpty(NULL, data, key);
    else add_size = BinaryTreeNode_Put(tree->root, data, key, tree->compareFunction);
    if (add_size) tree->size += 1;
}

void* BinaryTreeNode_Get(struct BinaryTreeNode* tree_node, void* key, int(*compareFunction)(void*, void*)) {
    if (!tree_node || !key || !key || !compareFunction) return NULL;
    int cmp = compareFunction(key, tree_node->key);
    if(cmp == 0) return tree_node->data;
    if(cmp < 0) return BinaryTreeNode_Get(tree_node->left, key, compareFunction);
    else return BinaryTreeNode_Get(tree_node->right, key, compareFunction);
}

void* BinaryTree_Get(BinaryTree* tree, void* key) {
    if(!tree || !key) return NULL;
    return BinaryTreeNode_Get(tree->root, key, tree->compareFunction);
}

void BinaryTreeNode_Destroy(struct BinaryTreeNode* node) {
    if (!node) return;
    BinaryTreeNode_Destroy(node->left);
    BinaryTreeNode_Destroy(node->right);
    free(node);
}

void BinaryTree_Destroy(BinaryTree* tree) {
    if(!tree) return;
    BinaryTreeNode_Destroy(tree->root);
    free(tree);
}

void BinaryTreeNode_Print(struct BinaryTreeNode* node) {
    if(!node) return;
    BinaryTreeNode_Print(node->left);
    printf("%p\n", node->data);
    BinaryTreeNode_Print(node->right);
}

void BinaryTree_Print(BinaryTree* tree) {
    if(!tree) return;
    BinaryTreeNode_Print(tree->root);
}