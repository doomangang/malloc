#include "../inc/ft_malloc.h"

t_heap g_heap ={NULL, NULL, NULL};

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
//temporal maximum size def
#define TINY_MAX_SIZE 128
#define SMALL_MAX_SIZE 1024

void *malloc(size_t size) {
    if (size <= 0) return NULL;

    if (size <= TINY_MAX_SIZE) {
        // TODO: tiny alloc
        return NULL;
    }
    else if (size <= SMALL_MAX_SIZE) {
        // TODO: small alloc logic
        return NULL;
    }
    else {
        return (allocate_large(size));
    }
}