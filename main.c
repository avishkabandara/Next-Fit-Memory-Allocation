#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sClass {
    int size;
    int remainingSize; // Tracks remaining space in the block
    bool isAllocated;
} sClass;

sClass *memory; // Array to represent class
int totalClass = 0; // Number of classes
int lastAllocatedIndex = -1; // Keeps track of the last allocated position

// Function to initialize memory blocks
void initializeMemory() {
    printf("Enter the number of Class for section: ");
    scanf("%d", &totalClass);

    memory = (sClass *)malloc(totalClass * sizeof(sClass));

    for (int i = 0; i < totalClass; i++) {
        printf("The number of students that can be in a class %d: ", i + 1);
        scanf("%d", &memory[i].size);
        memory[i].remainingSize = memory[i].size; // Initially, remaining size equals total size
        memory[i].isAllocated = false;
    }
}

// Function to allocate memory using Next Fit
void nextFitAllocate(int request) {
    if (lastAllocatedIndex == -1) {
        lastAllocatedIndex = 0; // Start from the first block if no previous allocation exists
    }

    int startIndex = lastAllocatedIndex;

    for (int i = 0; i < totalClass; i++) {
        int index = (startIndex + i) % totalClass; // Circular traversal

        if (memory[index].remainingSize >= request) {
            memory[index].remainingSize -= request; // subtract allocated size from remaining space
            memory[index].isAllocated = true; // Mark as allocated if not already
            lastAllocatedIndex = index; // Update the last allocated position
            printf("Class enrolled students is %d (Size: %d, Remaining: %d)\n", index + 1, memory[index].size, memory[index].remainingSize);
            return;
        }
    }

    printf("Students enroll failed. No suitable class found for size %d.\n", request);
}

// Function to deallocate a class
void deallocate(int classIndex) {
    if (classIndex < 1 || classIndex > totalClass) {
        printf("Invalid class index.\n");
        return;
    }

    if (memory[classIndex - 1].isAllocated) {
        memory[classIndex - 1].remainingSize = memory[classIndex - 1].size; // Reset remaining space
        memory[classIndex - 1].isAllocated = false;
        printf("Class %d deallocated successfully.\n", classIndex);
    } else {
        printf("Class %d is already free.\n", classIndex);
    }
}

// Function to display the class status
void displayMemory() {
    printf("\n Classes Status:\n");
    for (int i = 0; i < totalClass; i++) {
        printf("Class %d - Size: %d, Remaining: %d, %s\n", i + 1, memory[i].size, memory[i].remainingSize,memory[i].isAllocated ? " Allocated" : "Free");
    }
    printf("\n");
}

int main() {
    initializeMemory();
    displayMemory();

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Enroll to class\n");
        printf("2. Deallocate class\n");
        printf("3. Display classes Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int request;
                printf("Enter the number of student enroll to class: ");
                scanf("%d", &request);
                nextFitAllocate(request);
                break;
            }
            case 2: {
                int classIndex;
                printf("Enter the class number to deallocate: ");
                scanf("%d", &classIndex);
                deallocate(classIndex);
                break;
            }
            case 3:
                displayMemory();
                break;
            case 4:
                free(memory);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

