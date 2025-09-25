#include "../inc/ft_malloc.h"

t_heap g_heap ={NULL, NULL, NULL};

void *malloc(size_t size) {
    if (size <= 0) return NULL;

    if (size <= TINY_MAX_SIZE)
        return find_or_create_block(&g_heap.tiny, );
    else if (size <= SMALL_MAX_SIZE) {
        // TODO: small alloc logic
        return NULL;
    }
    else {
        return (allocate_large(size));
    }
}

void free(void* ptr) {
    if (!ptr)
        return ;

    t_block *block_meta = (t_block *)((void *)ptr - sizeof(t_block));

    //TODO: tiny and small
    free_large_block(block_meta);
}

