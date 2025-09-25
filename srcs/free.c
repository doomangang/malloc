#include "../inc/ft_malloc.h"

static void free_large_block(t_block* block_to_free) {
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

void free(void* ptr) {
    if (!ptr)
        return ;

    t_block *block_meta = (t_block *)((void *)ptr - sizeof(t_block));

    //TODO: tiny and small
    free_large_block(block_meta);
}