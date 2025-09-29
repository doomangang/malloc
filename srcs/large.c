#include "../inc/ft_malloc.h"

void *allocate_large(size_t size) {
    size_t total_size = sizeof(t_block) + size;

    t_block *new_block = mmap(NULL,
                            total_size,
                            PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANON,
                            -1, 0);
    if (new_block == MAP_FAILED)
        return NULL;
    
    new_block->size = total_size;
    new_block->is_free = 0;

    new_block->next = g_heap.large;
    g_heap.large = new_block;

    return ((void *)new_block + sizeof(t_block));
}

void free_large(t_block* block_to_free) {
    t_block* current = g_heap.large;
    t_block* prev = NULL;

    while (current) {
        if (current == block_to_free) {
            if (prev)
                prev->next = current->next;
            else
                g_heap.large = current->next;

            munmap(block_to_free, block_to_free->size);
            return;
        }
        prev = current;
        current = current->next;
    }
}
