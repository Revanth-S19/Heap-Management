#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 20000

// Simulating the heap with a static array.
unsigned char heap_memory[HEAP_SIZE];

typedef struct Block {
    int size;   // size allocated by user
    int free;   // 1 for free, 0 for allocated
    struct Block *next;
    struct Block *prev;
} Block;

Block *heap = NULL;

int initialize_heap() 
{
    int ret_val = 1;
    heap = (Block *)heap_memory;  // Pointing to the beginning of the static array
    
    if (!heap) 
    {
        printf("Heap initialization failed!\n");
        ret_val = 0;
    } 
    else 
    {
        // Set up the first block in the heap
        heap->size = HEAP_SIZE - sizeof(Block);  // Total available size
        heap->free = 1;  // Mark as free
        heap->prev = NULL;
        heap->next = NULL;
    }
    return ret_val;
}

void merge_free_blocks() 
{
    Block *current = heap;
    while (current && current->next) 
    {
        if (current->free && current->next->free) 
        {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
            if (current->next) 
            {
                current->next->prev = current;
            }
        } 
        else 
        {
            current = current->next;
        }
    }
}

void split_memory(Block *ptr, int size) 
{
    if (ptr->size >= size + sizeof(Block) + 1) 
    {
        // Ensure split leaves room for metadata (block size)
        Block *new_block = (Block *)((char *)ptr + sizeof(Block) + size);
        new_block->size = ptr->size - size - sizeof(Block);
        new_block->free = 1;
        new_block->prev = ptr;
        new_block->next = ptr->next;
        if (ptr->next) 
        {
            ptr->next->prev = new_block;
        }
        ptr->next = new_block;
        ptr->size = size;
    }
    ptr->free = 0;
}

void *allocate(int size) 
{
    Block *current = heap;

    while (current) 
    {
        if (current->free && current->size >= size) 
        {
            // Check if splitting would create a too-small leftover block
            if (current->size >= size + sizeof(Block) + 4)  
            {
                split_memory(current, size);
            }

            current->free = 0;
            return (void *)(current + 1);  // Returning memory after the block header
        }
        current = current->next;
    }

    printf("Memory allocation failed!\n");
    return NULL;
}

void free_memory(void *ptr) 
{
    if (!ptr || ptr < (void *)heap || ptr >= (void *)((char *)heap + HEAP_SIZE)) 
	{
        printf("Invalid free request!\n");
    } 
	else 
	{
        Block *block = (Block *)ptr - 1;  // Get the block pointer
        if (block->free) 
		{
            printf("Memory is already free at this address.\n");
        } 
		else 
		{
            block->free = 1;  // Mark the block as free

            merge_free_blocks();

            printf("Memory freed at %p\n", ptr);
        }
    }
}

void print_heap() 
{
    Block *curr = heap;
    printf("\nHeap Status:\n");
    printf("------------------------------------------------------------\n");
    printf("| %-10s | %-8s | %-16s |\n", "Status", "Size (bytes)", "Address to User");
    printf("------------------------------------------------------------\n");

    while (curr) 
    {
        // Print block's status, size and address to user
        printf("| %-10s | %-8d | %-16p |\n", 
               curr->free ? "FREE" : "ALLOCATED",   // Status of the block
               curr->size,                         // Size of the block
               curr->free ? NULL : (void *)(curr + 1)); // Address to user

        curr = curr->next;
    }

    printf("------------------------------------------------------------\n");
}

int main() 
{
    int flag = initialize_heap();
    printf("Initial heap state:\n");
    print_heap();

    int choice = 0;
    int size;
    void *ptr;

    if (flag)
    {
        while (choice != 4)
        {
            printf("\nMenu:\n1. Allocate memory\n2. Free memory\n3. Print heap\n4. Exit\nEnter your choice: ");
            if (scanf("%d", &choice) != 1) 
            {
                printf("Invalid input! Please enter a valid number between 1 and 4.\n");
                while (getchar() != '\n');
            }
            else
            {
                switch (choice) 
                {
                    case 1:
                        printf("Enter size to allocate: ");
                        scanf("%d", &size);
                        if (size > HEAP_SIZE) 
                        {
                            printf("Error: Size exceeds available heap space.\n");
                        }
                        else
                        {                        
                            ptr = allocate(size);
                            if (ptr) 
                            {
                                printf("Memory allocated at %p\n", ptr);
                            }
                            else
                            {
                                printf("Memory allocation failed!\n");
                            }
                        }
                        break;

                    case 2:
                        printf("Enter address to free: ");
                        scanf("%p", &ptr);
                        free_memory(ptr);
                        break;

                    case 3:
                        print_heap();
                        break;

                    case 4:
                        printf("Exiting...\n");
                        break;

                    default:
                        printf("Invalid choice! Please enter a valid number between 1 and 4.\n");
                        break;
                }
            }
        }
    }
    return 0;
}
