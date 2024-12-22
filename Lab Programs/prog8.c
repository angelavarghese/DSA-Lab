#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define node structure for expression tree
typedef struct Node {
    char *data;
    struct Node *left;
    struct Node *right;
} *NODE;

// Define stack structure
typedef struct stack {
    int top;
    NODE node[100]; // Increased stack size to 100 for larger expressions
} *STACK;

// Function prototypes
void push(STACK s, NODE item);
NODE pop(STACK s);
int precedence(char symbol);
NODE createNode(char *item);
void preorder(NODE root);
void inorder(NODE root);
void postorder(NODE root);
NODE create_expr_tree(char infix[]); 

int main() {
    char infix[100];
    NODE root = NULL;

    printf("\n Read the infix expression: ");
    //scanf("%s", infix); 

    // Example infix expression
    strcpy(infix, "12^13-17+1"); 

    root = create_expr_tree(infix);

    printf("\n The preorder traversal is\n");
    preorder(root);

    printf("\n The inorder traversal is\n");
    inorder(root);

    printf("\n The postorder traversal is\n");
    postorder(root);

    return 0;
}

// Function implementations

void push(STACK s, NODE item) {
    s->node[++(s->top)] = item;
}

NODE pop(STACK s) {
    return s->node[(s->top)--];
}

int precedence(char symbol) {
    switch (symbol) {
        case '^': return 5;
        case '*': return 4;
        case '/': return 3;
        case '+': return 2;
        case '-': return 1;
        default: return 0;
    }
}

NODE createNode(char *item) {
    NODE temp = (NODE)malloc(sizeof(struct Node));
    temp->data = strdup(item); // Allocate memory for data
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void preorder(NODE root) {
    if (root != NULL) {
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(NODE root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->data);
        inorder(root->right);
    }
}

void postorder(NODE root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->data);
    }
}

NODE create_expr_tree(char infix[]) { 
    STACK TS, OS;
    TS = (STACK)malloc(sizeof(struct stack));
    OS = (STACK)malloc(sizeof(struct stack));
    TS->top = -1;
    OS->top = -1;
    int i, j;
    char *token;
    NODE temp, t;

    for (i = 0; infix[i] != '\0'; i++) { 
        // Handle operands (numbers or variables)
        if (isalnum(infix[i])) {
            token = (char *)malloc(sizeof(char) * 10); // Increase token size for larger operands
            j = 0;
            while (isalnum(infix[i])) {
                token[j++] = infix[i++];
            }
            token[j] = '\0';
            temp = createNode(token);
            push(TS, temp);
            i--; 
        } 
        // Handle operators
        else {
            char operator[2] = {infix[i], '\0'}; 
            temp = createNode(operator);

            // Pop operators from OS with higher or equal precedence
            while (OS->top != -1 && precedence(OS->node[OS->top]->data[0]) >= precedence(infix[i])) {
                t = pop(OS);
                t->right = pop(TS);
                t->left = pop(TS);
                push(TS, t);
            }

            // Push the current operator to OS
            push(OS, temp);
        }
    }

    // Pop remaining operators from OS and construct the tree
    while (OS->top != -1) {
        t = pop(OS);
        t->right = pop(TS);
        t->left = pop(TS);
        push(TS, t);
    }

    return pop(TS);
}