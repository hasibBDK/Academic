#include <stdio.h>
#include <stdlib.h>

// Structure representing a node in the binary search tree
struct Node {
    int data;           // Data stored in the node
    struct Node* left;  // Pointer to the left child node
    struct Node* right; // Pointer to the right child node
};

// Function to create a new node with the given data
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // Allocate memory for the new node
    node->data = data;  // Set the data of the new node
    node->left = NULL;   // Initialize left child pointer to NULL
    node->right = NULL;  // Initialize right child pointer to NULL
    return node;         // Return the newly created node
}

// Function to insert a new node with the given data into the binary search tree
struct Node* insertNode(struct Node* root, int data) {
    // If the root is NULL, create a new node and return it
    if (root == NULL) {
        return newNode(data);
    }

    // If the data is less than the root's data, insert into the left subtree
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    // If the data is greater than the root's data, insert into the right subtree
    else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root; // Return the root of the modified binary search tree
}

// Function to perform an inorder traversal of the binary search tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        // Traverse the left subtree
        inorderTraversal(root->left);
        // Print the data of the current node
        printf("%d ", root->data);
        // Traverse the right subtree
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int keys[] = {8, 3, 10, 1, 6, 14, 4, 7, 13, 17, 14}; // Keys to insert into the binary search tree
    int len = sizeof(keys) / sizeof(keys[0]); // Calculate the length of the keys array

    // Insert each key into the binary search tree
    for (int i = 0; i < len; i++) {
        root = insertNode(root, keys[i]);
    }

    // Print the inorder traversal of the binary search tree
    printf("Inorder traversal of the binary search tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
