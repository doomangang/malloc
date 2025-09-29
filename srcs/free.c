#include "../inc/ft_malloc.h"
void free_block_in_zone(t_block* block_to_free) {
    block_to_free->is_free = 1;
    coalesce_adjacent_block(block_to_free);
}

void coalesce_adjacent_block(t_block *block) {
    if (block->next && block->next->is_free) {
        block->size += block->next->size;
        block->next = block->next->next;
    }
}
