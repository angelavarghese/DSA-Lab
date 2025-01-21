#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} * NODE;

NODE createNewNode(int x) {
    NODE newNode = (NODE)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

NODE insertBeginning(NODE head, int x) {
    if (head == NULL) { // Handle the case where the list is empty.
        head = createNewNode(x);
        head->next = head;
        return head;
    }
    
    NODE newNode = createNewNode(x);
    newNode->next = head->next;
    head->next = newNode; // Update the header's link to point to the new first node.

    return head;
}

NODE insertEnd(NODE head, int x) {
    NODE newNode = createNewNode(x);
    if (head == NULL) {
        head = newNode;
        head->next = head; // Circular list
        return head;
    }
    NODE cur = head;
    while (cur->next != head) {
        cur = cur->next;
    }
    cur->next = newNode;
    newNode->next = head; // Maintain circularity
    return head;
}

void display(NODE head) {
    if (head == NULL) {
        printf("No linked list\n");
        return;
    }
    NODE temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("HEAD\n");
}

NODE reverseCList(NODE head) {
    if (head == NULL || head->next == head) { // Empty or single-node list
        return head;
    }
    NODE prev = NULL, cur = head, temp;
    NODE tail = head;
    do {
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    } while (cur != head);
    tail->next = prev;  // Set the tail's next to the new head
    return prev;         // Return the new head
}

void addZero(NODE head1, NODE head2) {
    NODE temp1 = head1->next, temp2 = head2->next;
    int count1 = 0, count2 = 0;

    // Calculate the length of the first list
    while (temp1 != head1) {
        count1++;
        temp1 = temp1->next;
    }

    // Calculate the length of the second list
    while (temp2 != head2) {
        count2++;
        temp2 = temp2->next;
    }

    // Add leading zeros to the shorter list
    if (count1 > count2) {
        for (int i = 0; i < count1 - count2; i++) {
            head2 = insertBeginning(head2, 0);
        }
    } else {
        for (int i = 0; i < count2 - count1; i++) {
            head1 = insertBeginning(head1, 0);
        }
    }
}

NODE addNums(NODE head1, NODE head2) {
    NODE result = createNewNode(0); // Initialize the result list with a dummy node
    NODE t1 = head1->next, t2 = head2->next;
    NODE resTail = result;
    int carry = 0;

    while (t1 != head1 || t2 != head2 || carry) {
        int sum = carry;
        if (t1 != head1) {
            sum += t1->data;
            t1 = t1->next;
        }
        if (t2 != head2) {
            sum += t2->data;
            t2 = t2->next;
        }

        carry = sum / 10;
        resTail->next = createNewNode(sum % 10);
        resTail = resTail->next;
    }

    resTail->next = result; // Make the result list circular again
    return result->next; // Return the real head
}

int main() {
    int i;
    char first[20], second[20];
    NODE head1 = (NODE) malloc(sizeof(struct node));
    NODE head2 = (NODE) malloc(sizeof(struct node));
    head1->next = head1;
    head2->next = head2;

    printf("Read 1st number: ");
    scanf("%s", first);
    for (i = 0; first[i] != '\0'; i++) {
        head1 = insertEnd(head1, first[i] - '0');
    }
    printf("Display 1st number: ");
    display(head1);

    printf("Read 2nd number: ");
    scanf("%s", second);
    for (i = 0; second[i] != '\0'; i++) {
        head2 = insertEnd(head2, second[i] - '0');
    }
    printf("Display 2nd number: ");
    display(head2);

    // Add zeros to make both lists the same length
    addZero(head1, head2);
    display(head1);
    display(head2);

    // Perform the addition of the two numbers
    NODE result = addNums(head1, head2);
    printf("Display of result: ");
    display(result);

    return 0;
}
