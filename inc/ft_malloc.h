#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <unistd.h>
# include <sys/mman.h>

# define TINY_MAX_SIZE 128 // N
# define SMALL_MAX_SIZE 1024 // M
# define MIN_ALLOC_COUNT 100

# define ALIGNMENT 16

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

extern t_heap   g_heap;

static size_t   g_tiny_zone_size = 0;
static size_t   g_small_zone_size = 0;

/* ====================== FUNCTIONS ======================= */

/* -------------------- malloc_api.c ---------------------- */
void            *malloc(size_t size);
void            free(void* ptr);
void            *realloc(void *ptr, size_t size);
void            show_alloc_mem();

/* ------------------- zone_manager.c --------------------- */
void            *find_or_create_block(t_block **zone_head, size_t size);
static t_block  *find_free_block(t_block *zone_head, size_t size);
static void     split_block(t_block *block, size_t required_size);
static t_block  *create_new_zone(size_t zone_size);

/* ----------------------- large.c ------------------------- */
void            *allocate_large(size_t size);
static void     free_large(t_block* block_to_free);

/* ------------------------ free.c ------------------------- */
static void     free_block_in_zone(t_block* block_to_free);
void            coalesce_adjacent_block(t_block *block);

/* ------------------------ utils.c ------------------------- */
static size_t   align(size_t size);
static size_t   calculate_zone_size(size_t max_block_size);
size_t          get_tiny_zone_size(void);
size_t          get_small_zone_size(void);
void            *find_block_by_ptr(void *ptr);
static size_t   print_zone_allocs(const char *zone_name, t_block *zone_head);

#endif