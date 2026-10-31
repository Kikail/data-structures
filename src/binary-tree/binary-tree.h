//
// Created by killi on 31/10/2026.
//

#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <stdbool.h>

struct BinaryTreeNode {
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
    struct BinaryTreeNode* parent;
    void* data;
    void* key;
};

struct BinaryTreeNode* BinaryTreeNode_CreateEmpty(void* parent, void* data, void* key);
bool BinaryTreeNode_Put(struct BinaryTreeNode* tree_node, void* data, void* key, int(*compareFunction)(void*, void*));
void* BinaryTreeNode_Get(struct BinaryTreeNode* tree_node, void* key, int(*compareFunction)(void*, void*));
void BinaryTreeNode_Destroy(struct BinaryTreeNode* node);
void BinaryTreeNode_Print(struct BinaryTreeNode* node);

struct BinaryTree {
    struct BinaryTreeNode* root;
    int (*compareFunction)(void*, void*);
    unsigned int size;
};
typedef struct BinaryTree BinaryTree;

BinaryTree* BinaryTree_CreateEmpty(int(*compareFunction)(void*, void*));
void BinaryTree_Put(BinaryTree* tree, void* data, void* key);
void* BinaryTree_Get(BinaryTree* tree, void* key);
void BinaryTree_Destroy(BinaryTree* tree);
void BinaryTree_Print(BinaryTree* tree);


#endif //DATA_STRUCTURES_BINARY_TREE_H
