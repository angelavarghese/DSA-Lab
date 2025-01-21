#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the CDLL
typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} * NODE;

// Function to create a new node
NODE createNewNode(int data) {
    NODE newNode = (NODE)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
}

// Function to insert a new node at the end
NODE insertEnd(NODE head, int data) {
    if (head == NULL) {
        return createNewNode(data);  // If the list is empty, create a new node
    }
    NODE newNode = createNewNode(data);
    NODE temp = head;
    // Traverse to the last node (which points to the head)
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;  // Last node points to the new node
    newNode->prev = temp;  // New node's prev points to the last node
    newNode->next = head;  // New node points back to the head
    head->prev = newNode;  // Head's prev points to the new node
    return head;
}

// Function to display the list (both forward and backward)
void display(NODE head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    NODE temp = head;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

// Main function to test CDLL
int main() {
    NODE head = NULL;
    head = insertEnd(head, 10);
    head = insertEnd(head, 20);
    head = insertEnd(head, 30);

    printf("Circular Doubly Linked List: ");
    display(head);
    
    return 0;
}
