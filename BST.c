//
// Hamish Philip
// 13/07/23
//
// Code to implement a Binary Search Tree in C With test code
//

//for console logs and memory allocation
#include <stdlib.h>
#include <stdio.h>

// Represents a Node in a Tree
struct Node {
    int* val;
    struct Node* leftChild;
    struct Node* rightChild;
};

// Creates a new node for a given value and allocates memory
void* newNode(int val) {
    struct Node* node = malloc(sizeof (struct Node));
    node->val = malloc(sizeof (int));
    *node->val = val;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}

// displays the in order traversal of tree with the given root
int displayTree(struct Node* root){
    //base case
    if (root == NULL){
        return 0;
    }
    // display left branch, print itself, and display right branch
    displayTree(root->leftChild);
    printf("%d\n",*root->val);
    displayTree(root->rightChild);

    return 0;
}

// searches for a given value in the tree and returns that value's node
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

// Adds a given value to the tree
void* addNode(int val, struct Node* root){

    // base case, creates a new node and adds it to a leaf
    if (root == NULL) {
        return newNode(val);
    }

    // finds the correct leaf recursively by traveling down the tree
    if (*root->val == val){
        printf("Error: Value already in Tree\n");
    } else if (*root->val > val){
        root->leftChild = addNode(val, root->leftChild);
    }else if (*root->val < val){
        root->rightChild = addNode(val, root->rightChild);
    }

    // return the new tree
    return root;
}

// removes a node with the given value, return new root
void* delNode(struct Node* root, int val) {

    // Base case if value is not in tree
    if (root == NULL) {
        printf("Error: Value not in tree so cannot be removed\n");
        return root;
    }

    // recursively traverse down tree until node to delete is found.
    if (*root->val > val) {
        root->leftChild = delNode(root->leftChild, val);
        return root;
    } else if (*root->val < val) {
        root->rightChild = delNode(root->rightChild, val);
        return root;
    }
    // if node to delete is found

    //If one child is NULL
    //If both are NULL, Null is returned and leaf node is deleted
    // and so its parent's child is set to the returned NULL
    if (root->leftChild == NULL) {
        struct Node* child = root->rightChild;
        free(root);
        return child;
    } else if (root->rightChild == NULL) {
        struct Node* child = root->leftChild;
        free(root);
        return child;
    } else {
        // if Neither child is NULL

        struct Node* parent = root;

        // find the next node in the in order traversal
        struct Node* successor = root->rightChild;
        while (successor->leftChild != NULL) {
            parent = successor;
            successor = successor->leftChild;
        }

        // skip node to remove
        if (parent != root) {
            parent->leftChild = successor->rightChild;
        } else {
            parent->rightChild = successor->rightChild;
        }

        //swap values of root and next successor
        root->val = successor->val;

        //safely remove successor as it is a leaf node, ad its value has been moved up
        free(successor);
        return root;
    }
}

// Driver Code to test
int main() {

    printf("Building Tree...\n");
    //initialise tree
    struct Node* tree = addNode(5,NULL);
    //add nodes
    addNode(4,tree);
    addNode(3,tree);
    addNode(10,tree);
    addNode(7,tree);
    addNode(7,tree);


    //In order traversal
    printf("Tree:\n");
    displayTree(tree);

    //search tree
    printf("Searching for value 6...\n");
    struct Node* node6 = searchTree(6,tree);
    if (node6 != NULL) {
        printf("found: %d\n",*node6->val);
    }

    printf("Searching for value 3...\n");
    struct Node* node3= searchTree(3,tree);
    if (node3 != NULL) {
        printf("found: %d\n",*node3->val);
    }

    //delete nodes
    printf("Removing Value 10...\n");
    delNode(tree,10);
    printf("Removing Value 20...\n");
    delNode(tree,20);


    //In order traversal
    printf("New Tree:\n");
    displayTree(tree);

}