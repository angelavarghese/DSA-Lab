#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int data;
   struct node *left;
   struct node *right;
} *NODE;

NODE create_node(int item) {
   NODE temp = (NODE)malloc(sizeof(struct node));
   if (temp == NULL) {
       printf("Memory allocation failed!\n");
       exit(1); 
   }
   temp->data = item;
   temp->left = NULL;
   temp->right = NULL;
   return temp;
}

void inorder(NODE root) {
   if (root != NULL) {
       display(root->left);
       printf("%d ", root->data);
       display(root->right);
   }
}

void preorder(NODE root) {
   if (root != NULL) {
       printf("%d ", root->data);
       preorder(root->left);
       preorder(root->right);
   }
}

void postorder(NODE root) {
   if (root != NULL) {
       postorder(root->left);
       postorder(root->right);
       printf("%d ", root->data);
   }
}

int count_nodes(NODE root) {
   if (root == NULL) {
       return 0;
   } else {
       return (count_nodes(root->left) + count_nodes(root->right) + 1);
   }
}

int height(NODE root) {
   if (root == NULL) {
       return -1; 
   } else {
       int leftht = height(root->left);
       int rightht = height(root->right);
       return (leftht > rightht) ? (leftht + 1) : (rightht + 1);
   }
}

int leaf_nodes(NODE root) {
   if (root == NULL) {
       return 0;
   } else if (root->left == NULL && root->right == NULL) {
       return 1;
   } else {
       return leaf_nodes(root->left) + leaf_nodes(root->right);
   }
}

int nonleaf_nodes(NODE root) {
   if (root == NULL || (root->left == NULL && root->right == NULL)) {
       return 0;
   } else {
       return nonleaf_nodes(root->left) + nonleaf_nodes(root->right) + 1;
   }
}

NODE create_binary_tree(NODE root) {
    int x;
    if(root == NULL) { 
        printf("Enter data for root node (-1 for nothing): ");
        scanf("%d", &x);
        if (x == -1) {
            return NULL;
        }
        root = create_node(x); 
    }

    printf("Enter left child of %d (-1 for nothing): ", root->data);
    scanf("%d", &x);
    if (x != -1) {
        root->left = create_node(x);
        root->left = create_binary_tree(root->left);
    }

    printf("Enter right child of %d (-1 for nothing): ", root->data);
    scanf("%d", &x);
    if (x != -1) {
        root->right = create_node(x);
        root->right = create_binary_tree(root->right);
    }

    return root;
}

int main() {
    NODE root = NULL;

    root = create_binary_tree(root);

    printf("\n The tree(inorder) is\n");
    inorder(root);
    printf("\n");
    printf("\n The tree(preorder) is\n");
    preorder(root);
    printf("\n");
    printf("\n The tree(postorder) is\n");
    postorder(root);
    printf("\n");

    printf("\n The total number of nodes is %d\n", count_nodes(root));
    printf("\n The height of the tree is %d\n", height(root));
    printf("\n The total number of leaf nodes is %d\n", leaf_nodes(root));
    printf("\n The total number of non-leaf nodes is %d\n", nonleaf_nodes(root));

    return 0;
}