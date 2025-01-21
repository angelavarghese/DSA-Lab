#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    char ch;
    struct Node * next;
};
typedef struct Node * node;

node createNewNode(int x){
    node newNode = (node)malloc(sizeof(struct Node));
    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

node insertAtEnd(node head, int x){
    node temp = head;
    if(temp == NULL){
        return createNewNode(x);
    }

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createNewNode(x);
    return head;
}

node insertAtBeginning(node head, int x){
    node temp = createNewNode(x);
    if(temp == NULL){
        return head;
    }
    temp->next = head;
    return temp;
}

node deleteNode(node head, int x){ // return head node
    node prev, temp;
    if(head == NULL){ // if linked list does not exist
        printf("linked list no\n");
        return NULL;
    }
    if(head->data == x){ // if data at start of list
        temp = head;
        temp = temp->next;
        return temp;
    }
    prev = head;
    temp = head->next;
    while(temp != NULL){ // if data in middle or end of list
        if(temp->data == x){
            prev->next = temp->next;
            free(temp);
            return head;
        }
        prev = prev->next;
        temp = temp->next;
    }
    // if data not in the list
    printf("Data not found in linked list\n");
    return head;
}

void displayList(node head){
    node temp = head;
    if(temp == NULL){
        printf("Linked List does not exist!\n");
        return;
    }
    while(temp != NULL){
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

node reverseList(node head){
    if(head == NULL || head->next == NULL)
        return head;
    node revHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return revHead;
}

node reverseList_iter(node head) {
    if(head == NULL || head->next == NULL)
        return head;
    node temp, cur = head, prev = NULL;
    while(cur != NULL) {
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    return prev;
}

void splitList(node head){ // split list into two based on even odd
    printf("\nhihi\n");
    node cur = head;
    node evenhead = NULL;
    node oddhead = NULL;
    while(cur != NULL){
        if(cur->data % 2 == 0){
            evenhead = insertAtEnd(evenhead, cur->data); 
        } else{
            oddhead = insertAtEnd(oddhead, cur->data);
        }
        cur = cur->next;
    }
    printf("\ndisplay even list: ");
    displayList(evenhead);
    printf("\ndisplay odd list: ");
    displayList(oddhead);
}

int countNodes(node head){
    int count = 0;
    if(head == NULL){
        printf("Linked list does not exist");
        return 0;
    }
    node temp = head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

int findNode(node head, int pos){ // return found node
    if(head == NULL){
        printf("Linked list does not exist");
        return -1;
    }
    int count = 0;
    node temp = head;
    while(temp != NULL){
        if(count == pos){
            return temp->data;
        }
        temp = temp->next;
        count++;
    }
    printf("Node does not exist\n");
    return -1;
}

node removeDuplicates(node head){
    node cur = head;
    while(cur != NULL){
        while(cur->next != NULL && cur->next->data == cur->data){
            cur->next = cur->next->next;
        }
        cur = cur->next;
    }
    return head;
}

node mergeList(node head1, node head2){
    node merged = NULL;
    if(head1 == NULL)
        return head2;
    else if(head2 == NULL)
        return head1;
    else if(head1->data <= head2->data){
        merged = head1;
        merged->next = mergeList(head1->next, head2);
    } else{
        merged = head2;
        merged->next = mergeList(head1, head2->next);
    }
    return merged;
}

node swapNodes(node head, int x1, int x2){
    node node1, node2, temp, prev1, prev2;
    prev1 = prev2 = NULL;
    node1 = node2 = head;
    while(node1 != NULL && node1->data != x1){
        prev1 =  node1;
        node1 = node1->next;
    }
    while(node2 != NULL && node2->data != x2){
        prev2 = node2;
        node2 = node2->next;
    }
    if(node1 == NULL || node2 == NULL) // if nodes don't exist, return as is
        return head;
    
    // swapping nodes
    if(prev1 == NULL)
        head = node2;
    else
        prev1->next = node2;
    
    if(prev2 == NULL)
        head = node1;
    else
        prev2->next = node1;
    
    //swapping pointers
    temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
    return head;
}

node intersection_2Lists(node head1, node head2){
    node temp1 = head1, temp2 = head2, common;
    common = (node)malloc(sizeof(struct Node));
    while(temp1 != NULL){
        temp2 = head2;
        while(temp2 != NULL){
            if(temp2->data == temp1->data){
                common->data = temp1->data;
                common->next = NULL;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return common;
}

int main(){
    int x, n, choice;

    node head1 = createNewNode(1);
    head1 = insertAtEnd(head1,2);
    head1 = insertAtEnd(head1,7);
    head1 = insertAtEnd(head1,11);
    head1 = insertAtEnd(head1,13);

    node head2 = createNewNode(1);
    head2 = insertAtEnd(head2,3);
    head2 = insertAtEnd(head2,7);
    head2 = insertAtEnd(head2,9);
    head2 = insertAtEnd(head2,13);

    displayList(intersection_2Lists(head1, head2));

    while(1){
        printf("LINKED LIST OPERATIONS\n\n1. Reversing a singly linked list\n2. Split linked list based on data being even or odd\n3. Print the middle node data of the list\n4. Remove the duplicate values from the sorted linked list\n5. Merge two sorted linked lists into a single sorted list\n6. Swapping two alternative nodes without swapping the data of alternative nodes\nAny key to exit\n\nMAKE YOUR CHOICE:");
        scanf("%d",&choice);

        printf("Enter size of linkedlist: ");
        scanf("%d", &n);
        printf("Enter data for head node: ");
        scanf("%d", &x);
        node head = createNewNode(x);
        for(int i = 2; i <= n; i++){
            printf("Enter data for node %d: ", i);
            scanf("%d", &x);
            head = insertAtEnd(head, x);
        }
        
        switch(choice){
            case 1:
            printf("\n1. Reversing a singly linked list\n");
            printf("Before: ");
            display(head);
            printf("After: ");
            displayList(reverseList(head));
            break;

            case 2:
            printf("\n2. Split linked list based on data being even or odd\n");
            splitList(head);
            break;

            case 3:
            printf("\n3. Print the middle node data of the list\n");
            printf("Before: ");
            display(head);
            int len = countNodes(head);
            if(len %2 == 0){
                len = len/2;
                printf("Middle nodes: %d, %d", findNode(head, len), findNode(head,len+1));
            } else{
                len = len/2;
                printf("Middle nodes: %d, %d", findNode(head, len));
            }
            break;

            case 4:
            printf("4. Remove the duplicate values from the sorted linked list\n");
            printf("Before: ");
            display(head);
            printf("After: ");
            displayList(removeDuplicates(head));
            break;

            case 5:
            printf("\n5. Merge two sorted linked lists into a single sorted list\n");
            printf("Before: ");
            display(head);
            printf("After: ");
            displayList(mergeList(head1, head2));
            break;

            case 6:
            printf("6. Swapping two alternative nodes without swapping the data of alternative nodes\n");
            printf("Before: ");
            display(head);
            printf("After: ");
            displayList(mergeList(head1, head2));
            break;

            default:
            exit(0);
        }
    }
    return 0;
}