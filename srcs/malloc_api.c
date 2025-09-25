#include "../inc/ft_malloc.h"

t_heap g_heap ={NULL, NULL, NULL};

void *malloc(size_t size) {
    if (size <= 0) return NULL;

    size_t total_required_size = align(size + sizeof(t_block));

    if (size <= TINY_MAX_SIZE)
        return find_or_create_block(&g_heap.tiny, total_required_size);
    else if (size <= SMALL_MAX_SIZE) 
        return find_or_create_block(&g_heap.small, total_required_size);
    else
        return allocate_large(size);
}

void free(void* ptr) {
    if (!ptr)
        return ;

    t_block *block_meta = (t_block *)((void *)ptr - sizeof(t_block));

    //TODO: tiny and small
    free_large_block(block_meta);
}

