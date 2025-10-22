#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

typedef struct Stack {
    Node** array;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Node**) malloc(capacity * sizeof(Node*));
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    if(stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->array = (Node**) realloc(stack->array, stack->capacity * sizeof(Node*));
    }
    stack->array[++stack->top] = node;
}

Node* pop(Stack* stack) {
    if(isEmpty(stack)) return NULL;
    return stack->array[stack->top--];
}

Node* peek(Stack* stack) {
    if(isEmpty(stack)) return NULL;
    return stack->array[stack->top];
}

void inorderIterative(Node* root) {
    Stack* stack = createStack(100);
    Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    free(stack->array);
    free(stack);
}

void postorderIterative(Node* root) {
    if (root == NULL) return;
    Stack* stack1 = createStack(100);
    Stack* stack2 = createStack(100);

    push(stack1, root);
    while(!isEmpty(stack1)) {
        Node* node = pop(stack1);
        push(stack2, node);
        if(node->left) push(stack1, node->left);
        if(node->right) push(stack1, node->right);
    }
    while(!isEmpty(stack2)) {
        printf("%d ", pop(stack2)->data);
    }
    free(stack1->array); free(stack1);
    free(stack2->array); free(stack2);
}

void preorderIterative(Node* root) {
    if (root == NULL) return;
    Stack* stack = createStack(100);
    push(stack, root);
    while(!isEmpty(stack)) {
        Node* node = pop(stack);
        printf("%d ", node->data);
        if(node->right) push(stack, node->right);
        if(node->left) push(stack, node->left);
    }
    free(stack->array);
    free(stack);
}

Node* findParent(Node* root, int key) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return NULL;
    if ((root->left && root->left->data == key) || (root->right && root->right->data == key))
        return root;
    Node* leftSearch = findParent(root->left, key);
    if (leftSearch) return leftSearch;
    return findParent(root->right, key);
}

void printParent(Node* root, int key) {
    Node* parent = findParent(root, key);
    if (parent)
        printf("Parent of %d is %d\n", key, parent->data);
    else
        printf("Parent not found (either root node or not present)\n");
}

int treeHeight(Node* root) {
    if (root == NULL) return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int printAncestors(Node* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (printAncestors(root->left, key) || printAncestors(root->right, key)) {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}

int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int main() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);

    printf("Inorder Traversal: ");
    inorderIterative(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderIterative(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderIterative(root);
    printf("\n");

    printParent(root, 5);

    printf("Height of the tree: %d\n", treeHeight(root));

    printf("Ancestors of 5: ");
    if(!printAncestors(root, 5))
        printf("No ancestors found.\n");
    else
        printf("\n");

    printf("Number of leaf nodes: %d\n", countLeafNodes(root));

    return 0;
}
