#include <stdio.h>
#include <stdlib.h>

void heapify(int a[], int n, int i) {
    int largest = i;  // Initialize largest as root
    int l = 2 * i + 1;  // left child
    int r = 2 * i + 2;  // right child

    // If left child is larger than root
    if (l < n && a[l] > a[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && a[r] > a[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(a, n, largest);
    }
}

// Function to build a Max Heap
void buildHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

int main() {
    int n, i, a[10], ch;

    while (1) {
        printf("\n1. Create Heap\n2. Extract Max\n3. Exit\nRead choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Read no of elements: ");
                scanf("%d", &n);
                printf("Read elements: \n");
                for (i = 0; i < n; i++) {
                    scanf("%d", &a[i]);
                }
                buildHeap(a, n);
                printf("\nHeapified array:\n");
                for (i = 0; i < n; i++) {
                    printf("%d ", a[i]);
                }
                printf("\n");
                break;

            case 2:
                if (n > 0) {
                    printf("\nExtracted maximum: %d\n", a[0]);
                    a[0] = a[n - 1];
                    n--;
                    buildHeap(a, n);
                    printf("\nHeap after extraction:\n");
                    for (i = 0; i < n; i++) {
                        printf("%d ", a[i]);
                    }
                    printf("\n");
                } else {
                    printf("\nHeap is empty.\n");
                }
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}