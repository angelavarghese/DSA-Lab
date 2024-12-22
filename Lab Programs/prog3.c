#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define CHAR_SIZE 5

struct queue {
    int front, rear;
    char data[SIZE][CHAR_SIZE];
};
typedef struct queue * QUEUE;

QUEUE createQueue() {
    QUEUE q = (QUEUE)malloc(sizeof(struct queue));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); 
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

void send(QUEUE q, char item[CHAR_SIZE]) {
    if (q->front == (q->rear+1) % SIZE) 
        printf("\nQueue full.");
    else {
        q->rear = (q->rear+1) % SIZE;
        strcpy(q->data[q->rear], item);
        if(q->front == -1)
            q->front = 0;
    }
}

char * receive(QUEUE q) {
    char * del;
    if(q->front == -1) {
        printf("\nQueue empty");
        return NULL;
    }
    else {
        del = q->data[q->front];
        if(q->front == q->rear) {
            q->front = -1;
            q->rear = -1;
        } else {
            q->front = (q->front+1) % SIZE;
        }
        return del;
    }
}

void display(QUEUE q) {
    int i;
    if(q->front == -1)
        printf("\nQueue empty");
    else {
        printf("\nQueue content are \n");
        for(i = q->front; i != q->rear; i = (i+1)%SIZE) {
            printf("%s\n", q->data[i]);
        }
        printf("%s\n", q->data[q->rear]);
    }
    printf("-end\n");
}

int main() {
    int ch;
    char * del;
    char item[CHAR_SIZE];
    QUEUE q = createQueue(); // Create the queue dynamically

    for(;;) {
        printf("\n1. Send\n2. Receive\n3. Display\n4. Exit\nRead choice: ");
        scanf("%d", &ch);
        getchar();
        switch(ch) {
            case 1: 
                printf("\nRead msg to be sent: ");
                fgets(item, CHAR_SIZE, stdin);
                send(q, item);
                break;
            
            case 2: 
                del = receive(q);
                if(del != NULL)
                    printf("\n Element deleted is %s\n", del);
                    printf("-end\n");
                break;
            
            case 3:
                display(q);
                break;
            
            case 4:
                free(q); // Free the allocated memory
                return 0;
        }
    }
    return 0;
}