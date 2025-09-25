#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/mman.h>

# define TINY_MAX_SIZE 128 // N
# define SMALL_MAX_SIZE 1024 // M
# define MIN_ALLOC_COUNT 100


//memory block metadata
typedef struct s_block {
    size_t  size;
    int     is_free;
    struct s_block *next;
} t_block;

//heap for managing memory zones
//indicates tiny, small, large zone list starting point
typedef struct s_heap {
    t_block *tiny;
    t_block *small;
    t_block *large;
}t_heap;

extern t_heap g_heap;

static size_t g_tiny_zone_size = 0;
static size_t g_small_zone_size = 0;

#endif