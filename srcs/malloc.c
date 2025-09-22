#include "../inc/ft_malloc.h"

t_heap g_heap ={NULL, NULL, NULL};

void *allocate_large(size_t size) {
    (void)size;
}
void *allocate_small(size_t size) {    (void)size;
}
void *allocate_tiny(size_t size) {    (void)size;
}

//temporal maximum size def
#define TINY_MAX_SIZE 128
#define SMALL_MAX_SIZE 1024

void *malloc(size_t size) {
    if (size <= 0) return NULL;

    if (size <= TINY_MAX_SIZE) {
        // TODO: tiny alloc
        allocate_tiny(size);
        return (NULL);
    }
    else if (size <= SMALL_MAX_SIZE) {
        // TODO: small alloc logic
        allocate_small(size);
        return NULL;
    }
    else {
        return allocate_large(size);
    }
}