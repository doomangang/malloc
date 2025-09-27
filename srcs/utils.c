#include "../inc/ft_malloc.h"

static size_t align(size_t size) {
    return ((((size - 1) / ALIGNMENT) + 1) * ALIGNMENT);
}

static size_t calculate_zone_size(size_t max_block_size) {
    size_t pagesize = getpagesize();
    size_t min_required_size;

    min_required_size = (max_block_size + sizeof(t_block)) * 100;

    return (((min_required_size - 1) / pagesize) + 1) * pagesize;
}

size_t get_tiny_zone_size(void) {
    if (!g_tiny_zone_size)
        g_tiny_zone_size = calculate_zone_size(TINY_MAX_SIZE);
    return g_tiny_zone_size;
}

size_t get_small_zone_size(void) {
    if (!g_small_zone_size)
        g_small_zone_size = calculate_zone_size(SMALL_MAX_SIZE);
    return g_small_zone_size;
}

void *find_block_by_ptr(void *ptr) {
    if (!ptr) return ;

    t_block *curr = g_heap.tiny;
    while(curr) {
        if (curr == ptr)
            return g_heap.tiny;
        curr = curr->next;
    }

    curr = g_heap.small;
    while (curr) {
        if (curr == ptr)
            return g_heap.small;
        curr = curr->next;
    }

    curr = g_heap.large;
    while (curr) {
        if (curr == ptr)
            return g_heap.large;
        curr = curr->next;
    }

    return NULL;
}