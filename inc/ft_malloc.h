#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/mman.h>

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

#endif