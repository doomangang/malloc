#include "../inc/ft_malloc.h"

/**
 * @brief  Zone에서 가용 블록을 찾거나, 없으면 새 Zone을 만들어 블록을 할당한다.
 * @param  zone_head  수정 대상 Zone 리스트의 시작 포인터 주소 (e.g., &g_heap.tiny)
 * @param  required_size  실제로 필요한 총 크기 (sizeof(t_block) + 사용자 요청 크기)
 * @return            사용자에게 할당할 메모리 영역의 시작 주소
 */
void *find_or_create_block(t_block **zone_head, size_t required_size) {
    // find_free_block() 을 호출하여 가용 블럭을 찾아본다
    t_block *found_block = find_free_block(*zone_head, required_size);

    if (!found_block) {
        // 새로운 zone을 만든다
        size_t zone_size_to_create;

        if (required_size - sizeof(t_block) <= TINY_MAX_SIZE)
            zone_size_to_create = get_tiny_zone_size();
        else
            zone_size_to_create = get_small_zone_size();
        
        found_block = create_new_zone(zone_size_to_create);
        if (!found_block) return NULL;

        found_block->next = *zone_head;
        *zone_head = found_block;
    }
    //필요한 크기 만큼의 block을 split 하고 할당
    split_block(found_block, required_size);

    found_block->is_free = 0;
    return ((void *)found_block + sizeof(t_block));
}

t_block  *find_free_block(t_block *zone_head, size_t size) {
    t_block *curr = zone_head;

    while (curr) {
        if (curr->is_free == 1 && curr->size >= size)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void split_block(t_block *block, size_t required_size) {
    if (block->size < required_size + sizeof(t_block) + ALIGNMENT)
        return ;
    
    t_block *remainder_block = (t_block *)((void *)block + required_size);
    remainder_block->size = block->size - required_size;
    remainder_block->is_free = 1;

    remainder_block->next = block->next;
    block->next = remainder_block;
    block->size = required_size;
}

t_block *create_new_zone(size_t zone_size) {
    t_block *new_zone = mmap(NULL,
                            zone_size,
                            PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANON,
                            -1, 0);
    if (new_zone == MAP_FAILED)
        return NULL;

    new_zone->is_free = 1;
    new_zone->next = NULL;
    new_zone->size = zone_size;
    
    return new_zone;
}