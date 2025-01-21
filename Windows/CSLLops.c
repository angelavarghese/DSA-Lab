#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct node {
    int data;
    struct node *next;
} * NODE;

NODE createNewNode(int x) {
    NODE newNode = (NODE)malloc(sizeof(struct node));
    if(newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

NODE insertEnd(NODE tail, int x) { // is this for circular linkedlist?
    NODE newNode = createNewNode(x);
    if(tail == NULL || tail->next == NULL) { // if list is empty
        newNode->next = newNode; 
        tail = newNode;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode; // moving tail to new end
    }
    printf("Inserted %d at end successfully\n", x);
    return tail;
}

NODE insertBeginning(NODE tail, int x) {
    NODE newNode = createNewNode(x);
    if(tail == NULL) { // if list is empty
        tail = newNode;
        newNode->next = newNode; 
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
    }
    printf("Inserted %d at beginning successfully\n", x);
    return tail;
}

NODE deleteBeginning(NODE tail) {
    if (tail == NULL){
        printf("Linkedlist empty\n");
        return NULL;
    }
    NODE temp = tail->next;
    tail->next = temp->next;
    printf("First element %d deleted\n", temp->data);
    free(temp);
    return tail;
}

NODE deleteEnd(NODE tail) {
    if (tail == NULL){
        printf("Linkedlist empty\n");
        return NULL;
    }
    NODE temp = tail->next;
    while (temp->next != tail) { // traverse to second last node
        temp = temp->next;
    }
    temp->next = tail->next;
    tail = temp;
    printf("Last element deleted\n");
    return tail;
}

NODE deleteAtPosition(NODE tail, int pos) {
    int i = 0;
    if (tail == NULL){
        printf("Linkedlist empty\n");
        return NULL;
    }
    NODE temp = tail->next;
    while (i < pos && temp != NULL){
        temp = temp->next;
        i++;
    }
    if(temp == NULL){
        printf("Position not present\n");
        return NULL;
    }
    NODE position = temp->next;
    temp->next = position->next;
    printf("%dth element %d deleted\n", pos, position->data);
    free(position);
    return tail;
}

void displayCLL(NODE);

NODE deleteEveryKthNodeIterative(NODE tail, int k) {
    if (tail == NULL || tail->next == tail) {
        printf("List is empty or has only one node.\n");
        return tail;
    }
    NODE current = tail->next; // Start from the head.
    NODE prev = tail;          // Tail points to the last node.
    int count = 1;
    while (tail->next != tail) { // Stop when only one node remains.
        count++;
        if (count == k) { // Found the k-th node to delete.
            printf("Deleting node with value: %d\n", current->data);
            prev->next = current->next;
            if (current == tail) {
                tail = prev; // Update the tail if the k-th node is the tail.
            }
            free(current);
            current = prev->next; // Move to the next node.
            count = 0;            // Reset count.
        } else {
            prev = current;
            current = current->next;
        }
    }
    printf("Last remaining node is: %d\n", tail->data);
    return tail; // Return the last node.
}

NODE deleteEveryKthNodeRecursive(NODE tail, int k) {
    if (tail == NULL || tail->next == tail) {
        // Base case: Only one node remains or the list is empty.
        if (tail) printf("Last remaining node is: %d\n", tail->data);
        return tail;
    }

    NODE current = tail->next; // Start from the head.
    NODE prev = tail;          // The node before the current node.

    // Traverse to the \( k \)-th node.
    for (int i = 1; i < k; i++) {
        prev = current;
        current = current->next;
    }

    // Delete the \( k \)-th node.
    printf("Deleting node with value: %d\n", current->data);
    prev->next = current->next;
    if (current == tail) {
        tail = prev; // Update tail if we are deleting the last node.
    }
    free(current);

    // Recursively delete the next \( k \)-th node.
    return deleteEveryKthNodeRecursive(tail, k);
}

void displayCLL(NODE tail) {
    if (tail == NULL) {
        printf("No linked list present\n");
        return;
    }

    NODE temp = tail->next;
    if (temp == NULL) {
        printf("Empty circular linked list\n");
        return;
    }

    do {
        // printf("why segfault? 2\n");
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != tail->next && temp != NULL);
    printf("*%d*\n", tail->next->data);
}

int main() {
    NODE tail = createNewNode(1);
    tail->next = tail; // Create initial circular list.
    for (int i = 2; i <= 9; i++) {
        tail = insertEnd(tail, i);
    }

    printf("Initial Circular Linked List:\n");
    displayCLL(tail);

    printf("\nDeleting every 4th node (iterative):\n");
    tail = deleteEveryKthNodeIterative(tail, 4);

    printf("\nResetting the list...\n");
    tail = createNewNode(1);
    tail->next = tail;
    for (int i = 2; i <= 9; i++) {
        tail = insertEnd(tail, i);
    }

    printf("\nDeleting every 4th node (recursive):\n");
    tail = deleteEveryKthNodeRecursive(tail, 4);

    return 0;
}
