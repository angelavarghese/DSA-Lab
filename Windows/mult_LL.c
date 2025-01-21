#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct node {
    int co, po;
    struct node *next;
} * NODE;

NODE insertEnd(NODE head, int co, int po) {
    NODE temp, cur;
    temp = (NODE)malloc(sizeof(struct node));
    temp->co = co;
    temp->po = po;
    temp->next = NULL;

    if(head == NULL) {
        return temp;
    }
    cur = head;
    while(cur->next != NULL)
        cur = cur->next;
    cur->next = temp;
    return head;
}

void display(NODE head) {
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }
    NODE temp = head;
    int first = 1; // Track if it's the first term to handle the sign properly.

    while (temp != NULL) {
        if (temp->co != 0) { // Skip terms with zero coefficient.
            if (!first) {
                if (temp->co > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            } else {
                if (temp->co < 0) {
                    printf("-");
                }
                first = 0;
            }

            int abs_co = abs(temp->co); // Handle absolute value for coefficient.

            if (temp->po == 0) { // Constant term.
                printf("%d", abs_co);
            } else if (temp->po == 1) { // Linear term.
                if (abs_co == 1) {
                    printf("x");
                } else {
                    printf("%dx", abs_co);
                }
            } else { // Higher-degree terms.
                if (abs_co == 1) {
                    printf("x^%d", temp->po);
                } else {
                    printf("%dx^%d", abs_co, temp->po);
                }
            }
        }
        temp = temp->next;
    }
    printf("\n");
}

NODE addterm(NODE res, int co, int po) {
    NODE temp, cur;
    temp = (NODE)malloc(sizeof(struct node));
    temp->co = co;
    temp->po = po;
    temp->next = NULL;
    if (res == NULL)
        return temp;
    cur = res;
    while(cur != NULL) {
        if (cur->po == po) {
            cur->co += co;
            return res;
        }
        cur = cur->next;
    }
    if(cur == NULL) {
        res = insertEnd(res, co, po);
    }
    return res;
}

NODE multiply(NODE poly1, NODE poly2) {
    NODE p1, p2, res = NULL;
    for(p1 = poly1; p1 != NULL; p1 = p1->next){
        for(p2 = poly2; p2 != NULL; p2 = p2->next) {
            res = addterm(res, p1->co * p2->co, p1->po + p2->po);
        }
    }
    return res;
}

int main() {
    NODE poly1 = NULL, poly2 = NULL, poly;
    int co, po;
    int i, n, m;
    printf("Read no of terms of 1st polynomial: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        printf("Read CO and PO of %d term: ", i+1);
        scanf("%d %d", &co, &po);
        poly1 = insertEnd(poly1, co, po);
    }
    printf("1st Polynomial is: ");
    display(poly1);
    printf("\n");
    
    printf("Read no of terms of 2nd polynomial: ");
    scanf("%d", &m);
    for(i = 0; i < m; i++){
        printf("Read CO and PO of %d term: ", i+1);
        scanf("%d %d", &co, &po);
        poly2 = insertEnd(poly2, co, po);
    }
    printf("2nd Polynomial is: ");
    display(poly2);
    printf("\n");

    poly = multiply(poly1, poly2);
    printf("Result polynomial: ");
    display(poly);
    printf("\n");
    return 0;
}
