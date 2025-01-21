#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node * prev;
    struct Node * next;
} * node;

node createNewNode(int x){
    node newNode = (node)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

node insertEnd(node head, int x){
    if(head == NULL)
        return createNewNode(x);
    node cur = head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = createNewNode(x);
    return head;
}
node insertBeginning(node head, int x) {
    node newNode = createNewNode(x);
    if (head == NULL) { // If the list is empty, the new node is the only node in the list
        return newNode;
    }
    // Inserting the new node at the beginning
    newNode->next = head;      // New node's next points to the current head
    newNode->prev = NULL;      // New node's prev points to NULL, as it's now the first node
    head->prev = newNode;      // The current head's prev points to the new node

    // Update the head to the new node
    head = newNode;
    return head;
}


void backwardTraversal(node tail){
    node cur;
    while(cur != NULL){
        printf(" %d ", cur->data);
        cur = cur->prev;
    }
    printf("\n");
}

int main(){
    node head = createNewNode(1);
    head = insertEnd(head,2);
    head = insertEnd(head,3);
    head = insertEnd(head,4);
    head = insertEnd(head,5);

    printf("Backward traversal\n");
    backwardTraversal(head);

    free(head);

    return 0;
}