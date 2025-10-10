#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Compute the height of the tree
int height(Node* root) {
    if (!root) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Print spaces
void printSpaces(int n) {
    for (int i = 0; i < n; i++)
        printf(" ");
}

// Print tree level by level
void printTreeLevels(Node* root) {
    int h = height(root);
    int maxWidth = (int)pow(2, h) - 1; // max nodes in bottom level
    Node* queue[1024];                 // simple queue for BFS
    int front = 0, rear = 0;
    queue[rear++] = root;

    for (int level = 0; level < h; level++) {
        int levelNodes = (int)pow(2, level); // nodes at current level
        int spaceBefore = (int)pow(2, h - level) - 1;
        int spaceBetween = (int)pow(2, h - level + 1) - 1;

        printSpaces(spaceBefore);

        for (int i = 0; i < levelNodes; i++) {
            Node* node = queue[front++];
            if (node) {
                printf("%d", node->data);
                queue[rear++] = node->left;
                queue[rear++] = node->right;
            } else {
                printf(" ");
                queue[rear++] = NULL;
                queue[rear++] = NULL;
            }
            printSpaces(spaceBetween);
        }
        printf("\n");
    }
}

int main() {
    // Example tree
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Binary Tree:\n\n");
    printTreeLevels(root);

    return 0;
}
