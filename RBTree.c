//
// Hamish Philip
// 13/07/23
//

#include <stdlib.h>
#include <stdio.h>

struct Node {
    int* val;
    struct Node* leftChild;
    struct Node* rightChild;
};

void* newNode(int val) {
    struct Node* node = malloc(sizeof (struct Node));
    node->val = malloc(sizeof (int));
    *node->val = val;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}

int displayTree(struct Node* root){
    if (root == NULL){
        return 0;
    }
    displayTree(root->leftChild);
    printf("%d\n",*root->val);
    displayTree(root->rightChild);

    return 0;
}

struct Node* searchTree(int val, struct Node* root){
    if (root != NULL){
        if (*root->val == val) {
            return root;
        } else if (*root->val > val) {
            return searchTree(val,root->leftChild);
        } else if (*root->val < val) {
            return searchTree(val,root->rightChild);
        }
    }

    printf("Error: Value not in tree\n");
    return NULL;
}

void* addNode(int val, struct Node* root){

    if (root == NULL) {
        return newNode(val);
    }

    if (*root->val == val){
        printf("Error: Value already in Tree");
    } else if (*root->val > val){
        root->leftChild = addNode(val, root->leftChild);
    }else if (*root->val < val){
        root->rightChild = addNode(val, root->rightChild);
    }

    return root;
}

int main() {
    //initialise tree
    struct Node* tree = NULL;

    //add node
    tree = addNode(3,tree);
    addNode(2,tree);
    addNode(6,tree);
    addNode(5,tree);

    //In order traversal
    displayTree(tree);

    //search tree
    struct Node* node = searchTree(6,tree);
    printf("%d\n",*node->val);

};