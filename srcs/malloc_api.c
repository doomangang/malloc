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

    t_block *block_type = find_block_by_ptr(block_meta);
    if (block_type == g_heap.small || block_type == g_heap.tiny)
        free_block_in_zone(block_meta);
    else
        free_large(block_meta);
}

void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);
    if (!size) {
        free(ptr);
        return malloc(0);
    }
    
    t_block *zone = (t_block *)find_block_by_ptr(ptr - sizeof(t_block));
    if (!zone) return NULL;
    size_t required_size = size + sizeof(t_block);

    t_block *block = (t_block *)(ptr - sizeof(t_block));

    /*
    * 1. shrinking
    * 2. growing
    * 2 - 1. 옆 블록이 있고 resize 하기 충분할 때
    * -> 옆 블록과 coalesce 하고 new size 만큼 split 해서 원래 주소 반환
    * 2 - 2. 옆 블록이 있는데 not free / 크기 충분치 않음
    * 2 - 3. 옆 블록이 없음
    * -> 새로운 블록 크기만큼 malloc 하고 블록 zone 에 연결 후 새 포인터 반환 / 기존 ptr 해당하는 부분은 free? / large - small/tiny logic 은 모두 같은지?
    */

    if (size < block->size) {
        if (zone == g_heap.tiny || zone == g_heap.small)
            split_block(block, size + sizeof(t_block));
        return ptr;
    }
    if (zone == g_heap.small || zone == g_heap.tiny && block->next 
        && block->next->size + block->size >= required_size) 
    {
        coalesce_adjacent_block(block);
        split_block(block, required_size);
        return ptr;
    }

    void* new_ptr = malloc(size);
    if (!new_ptr) return NULL;
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);

    return new_ptr;
}

/*
* printer format:
* TINY : 0xA0000
* 0xA0020 - 0xA004A : 42 bytes
* 0xA006A - 0xA00BE : 84 bytes
* SMALL : 0xAD000
* 0xAD020 - 0xADEAD : 3725 bytes
* LARGE : 0xB0000
* 0xB0020 - 0xBBEEF : 48847 bytes
* Total : 52698 bytes
* */

void show_alloc_mem()
{
    size_t total_allocated = 0;
    
    total_allocated += print_zone_allocs("TINY", g_heap.tiny);
    total_allocated += print_zone_allocs("SMALL", g_heap.small);
    total_allocated += print_zone_allocs("LARGE", g_heap.large);

    ft_printf("Total : %zu bytes\n", total_allocated);
}