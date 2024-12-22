#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define node structure for expression tree
typedef struct node {
    char *data;
    struct node *left;
    struct node *right;
} * NODE;

// Define stack structure
typedef struct stack {
    int top;
    NODE data[10];
} * STACK;

// Function prototypes
void push(STACK s, NODE item);
NODE pop(STACK s);
int precedence(char symbol); // Changed name for clarity
NODE createNode(char *item); // Changed name for consistency
void preorder(NODE root);
void inorder(NODE root);
void postorder(NODE root);
NODE create_expr_tree(NODE root, char infix[10]);

int main() {
    char infix[10];
    NODE root = NULL;

    printf("\nseg fault where?? 1\n");
    printf("\n Read the infix expression: ");
    //scanf("%s", infix);
    
    infix[0] = '1';
    infix[1] = '+';
    infix[2] = '2';
    infix[3] = '-';
    infix[4] = '3';
    root = create_expr_tree(root, infix);

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
    s->data[++(s->top)] = item;
}

NODE pop(STACK s) {
    return s->data[(s->top)--];
}

int precedence(char symbol) { // Changed name for clarity
    switch (symbol) {
        case '$': return 5;
        case '*': return 4;
        case '/': return 3;
        case '+':return 2;
        case '-': return 1;
        default: return 0;
    }
}

NODE createNode(char *item) { // Changed name for consistency
    NODE temp = (NODE) malloc(sizeof(struct node));
    temp->data = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void preorder(NODE root) {
    if (root != NULL) {
        printf("%s", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(NODE root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s", root->data);
        inorder(root->right);
    }
}

void postorder(NODE root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s", root->data);
    }
}

NODE create_expr_tree(NODE root, char infix[10]) {
    STACK TS, OS;
    TS->top = -1;
    OS->top = -1;
    int i;
    char symbol;
    NODE temp, t;
    char * token = (char *) malloc(sizeof(char)*3);
    printf("\nseg fault where?? 1\n");
    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];
        strcpy(token, "");
        // to see if double digit
        int j = 0; 
        while(i < strlen(infix) && isalnum(infix[i]) ) {
            token[j] = infix[i] ;
            j++;
            i++;
        }
        if(token != NULL) {
            temp = createNode(token);
        } else {
            temp = createNode(&infix[i]);
            if (OS->top == -1) {
                push(OS, temp);
            } else {
                while (OS->top != -1 && precedence(OS->data[OS->top]->data[0]) >= precedence(symbol)) {
                    t = pop(OS);
                    t->right = pop(TS);
                    t->left = pop(TS);
                    push(TS, t);
                }
                push(OS, temp);
            }
        }
    }

    while (OS->top != -1) {
        t = pop(OS);
        t->right = pop(TS);
        t->left = pop(TS);
        push(TS, t);
    }

    return pop(TS);
}