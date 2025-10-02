#include "../inc/ft_malloc.h"

size_t align(size_t size) {
    return ((((size - 1) / ALIGNMENT) + 1) * ALIGNMENT);
}

size_t calculate_zone_size(size_t max_block_size) {
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
    if (!ptr) return NULL;

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

/**
 * @brief  특정 Zone 리스트를 순회하며 할당된 블록 정보를 출력하고 총량을 반환
 * @param  zone_name  "TINY", "SMALL", "LARGE" 같은 Zone 이름
 * @param  zone_head  해당 Zone 리스트의 시작 포인터
 * @return            해당 Zone에서 할당된 총 바이트 수
 */
size_t print_zone_allocs(const char *zone_name, t_block *zone_head)
{
    size_t total_bytes = 0;

    ft_printf("%s : %p\n", zone_name, zone_head);

    t_block *current = zone_head;
    while (current)
    {
        if (!current->is_free)
        {
            void *start_addr = (void *)current + sizeof(t_block);
            void *end_addr = (void *)current + current->size;
            size_t user_size = current->size - sizeof(t_block);

            ft_printf("%p - %p : %u bytes\n", end_addr, start_addr, (unsigned int)user_size);
            
            total_bytes += user_size;
        }
        current = current->next;
    }
    return (total_bytes);
}