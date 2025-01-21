#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

typedef struct queue {
    int front, rear;
    char data[SIZE][5];
} *QUEUE;

void send(QUEUE q, char item[5]) {
    if (q->front == (q->rear + 1) % SIZE) {
        printf("\nQueue Full");
        return;
    }
    q->rear = (q->rear + 1) % SIZE;
    strncpy(q->data[q->rear], item, 4); // Truncate input to 4 characters
    q->data[q->rear][4] = '\0'; // Ensure null-termination
    if (q->front == -1) {
        q->front = 0;
    }
}

char *receive(QUEUE q) {
    if (q->front == -1) {
        printf("\nQueue is empty");
        return NULL;
    }
    char *del = malloc(5 * sizeof(char)); // Allocate memory for the dequeued item
    strncpy(del, q->data[q->front], 5);
    del[4] = '\0'; // Ensure null-termination
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    return del;
}

void display(QUEUE q) {
    if (q->front == -1) {
        printf("\nQueue empty");
        return;
    }
    printf("Queue content\n");
    int i;
    for (i = q->front; i != q->rear; i = (i + 1) % SIZE) {
        printf("%s\n", q->data[i]);
    }
    printf("%s\n", q->data[i]); // Print the last element
}

int main() {
    int ch;
    char *del;
    char item[20];
    QUEUE q = malloc(sizeof(struct queue)); // Allocate memory for the queue
    q->front = -1;
    q->rear = -1;

    for (;;) {
        printf("\n1. Send\n2. Receive\n3. Display\n4. Exit");
        printf("\nRead Choice: ");
        scanf("%d", &ch);
        getchar(); // To consume the newline character left by scanf

        switch (ch) {
            case 1:
                printf("\nRead msg to be sent: ");
                scanf("%19[^\n]", item); // Read a string with spaces
                send(q, item);
                break;
            case 2:
                del = receive(q);
                if (del != NULL) {
                    printf("\nElement received: %s\n", del);
                    free(del); // Free the memory allocated in `receive`
                }
                break;
            case 3:
                display(q);
                break;
            default:
                free(q); // Free allocated memory for the queue
                exit(0);
        }
    }
    return 0;
}
