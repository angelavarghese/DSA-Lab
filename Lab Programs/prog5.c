#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int count;

typedef struct node {
    int data;
    struct node * next;
} * NODE;

NODE insertEnd(NODE last, int item) {
    NODE temp;
    if(count >= SIZE) {
        printf("\nQueue Full.");
        return last;
    }
    count++;
    temp = (NODE)malloc(sizeof(struct node));
    temp->data = item;
    if(last == NULL) {
        temp->next = temp;
        last = temp;
    } else {
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
    return last;
}

NODE deleteBeginning(NODE last) {
    NODE temp = (NODE)malloc(sizeof(struct node));
    if(count <= 0) {
        printf("\nQueue Empty.");
        return last;
    }
    count--;

    if(last->next == last) {
        printf("\nElement deleted is %d\n", last->data);
        free(last);
        return NULL;
    } else {
        temp = last->next;
        last->next = temp->next;
        printf("ELement deleted is %d\n", temp->data);
        free(temp);
        return last;
    }
}

void display(NODE last) {
    if (last == NULL) {
        printf("\n Queue is empty\n");
        return;
    }

    printf("\n Queue Content are:\n");
    NODE temp = last->next; 
    do {
        printf("%d\t", temp->data);
        temp = temp->next;
    } while (temp != last); 
    printf("%d\t", last->data);
    printf("\n"); 
}

int main() {
    NODE last = NULL;
    int item, ch;

    for (;;) {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit");
        printf("\nRead Choice :");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("\n Read data to be inserted:");
                scanf("%d", &item);
                last = insertEnd(last, item);
                break;

            case 2:
                last = deleteBeginning(last);
                break;

            case 3:
                display(last);
                break;

            default:
                exit(0);
        }
    }

    return 0;
}