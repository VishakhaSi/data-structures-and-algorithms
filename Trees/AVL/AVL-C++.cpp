#include <iostream>
using namespace std;

// Node structure for AVL tree
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node
Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

// Function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Function to insert a node into the AVL tree
Node* insertNode(Node* root, int key) {
    if (root == nullptr)
        return createNode(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balance = getBalance(root);

    // Left Left case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to print the AVL tree in inorder traversal
void inorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}

int main() {
    Node* root = nullptr;

    // Inserting nodes into AVL tree
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    cout << "Inorder traversal of the AVL tree: ";
    inorderTraversal(root);

    return 0;
}
