#include <stdio.h>

#define TABLE_SIZE 10
#define PRIME 7

int hash_table[TABLE_SIZE] = {0};
int hash1(int key){
    return key % TABLE_SIZE;
}

int hash2(int key){
    return PRIME - (key % PRIME);
}

void hash_table_insert(int element) {
    int index1 = hash1(element);
    int index2 = hash2(element);
    int i = 0;

    while(hash_table[(index1 + i * index2) % TABLE_SIZE] != 0){
        i++;
        if (i >= TABLE_SIZE) {
            printf("ERROR: Table Full, insertion failed.\n");
            return;
        }
    }
    hash_table[(index1 + i * index2) % TABLE_SIZE] = element;
}

void hash_table_delete(int element) {
    int index1 = hash1(element);
    int index2 = hash2(element);
    int i = 0;

    while(hash_table[(index1 + i * index2) % TABLE_SIZE] != element){
        i++;
        if (i >= TABLE_SIZE) {
            printf("Element not found.\n");
            return;
        }
    }
    hash_table[(index1 + i * index2) % TABLE_SIZE] = -1;
    printf("Element %d deleted.\n", element);
}

void print_table() {
    printf("Hash Table\n");
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t----\t%d\n",i, hash_table[i]);
    }
}

int main() {

    // hash_table_insert(10);
    // hash_table_insert(13);
    // hash_table_insert(112);
    // hash_table_insert(11);
    // hash_table_insert(190);
    // hash_table_insert(80);
    // hash_table_insert(202);
    // hash_table_insert(300);
    // hash_table_insert(480);
    // hash_table_insert(1000);

    // print_table();


    int choice, element;
    while(1){
        printf("\n----\tHash Table Operations\t----\n1. Insert\n2. Delete\n3. Display\n4. Exit\n\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                hash_table_insert(element);
                break;

            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                hash_table_delete(element);
                break;  

            case 3:
                print_table();
                break;

            case 4:
                exit(0);
            default: 
                printf("!! Invalid Choice !!\nTry again.");
                break;
        }
    }

    return 0;
}