# --- Colors for fancy output ---
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

NAME_BASE = libft_malloc
ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)-$(shell uname -s)
endif

NAME = $(NAME_BASE)_$(HOSTTYPE).so
SYM_NAME = libft_malloc.so

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/free.c $(SRCS_DIR)/large.c $(SRCS_DIR)/malloc_api.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/zone_manager.c # 등등...
OBJS = $(SRCS:.c=.o)

# --- 라이브러리 경로 설정 ---
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ft_printf
PRINTF_A = $(PRINTF_DIR)/libftprintf.a

# --- 컴파일 및 링크 설정 ---
CC = gcc
CFLAGS = -Wall -Wextra -Werror
# 헤더 경로 추가 (-Ift_printf)
LFLAGS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

all: $(NAME)

$(NAME): $(LIBFT_A) $(PRINTF_A) $(OBJS)
	@echo "$(YELLOW)Linking object files to create shared library: $(NAME)...$(RESET)"
	# 링크 명령어에 $(LFLAGS) 사용
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LFLAGS)
	@echo "$(YELLOW)Creating symbolic link: $(SYM_NAME) -> $(NAME)...$(RESET)"
	@ln -sf $(NAME) $(SYM_NAME)
	@echo "$(GREEN)✓ Malloc library successfully created!$(RESET)"

# libft.a 빌드 규칙
$(LIBFT_A):
	@echo "$(YELLOW)Building dependency: libft.a...$(RESET)"
	@make -C $(LIBFT_DIR)

# libftprintf.a 빌드 규칙 (새로 추가)
$(PRINTF_A):
	@echo "$(YELLOW)Building dependency: libftprintf.a...$(RESET)"
	@make -C $(PRINTF_DIR)

%.o: %.c
	@echo "$(YELLOW)Compiling malloc source: $<...$(RESET)"
	# 헤더 검색 경로에 inc와 ft_printf 추가
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc -I$(PRINTF_DIR)

clean:
	@echo "$(YELLOW)Cleaning malloc object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean

fclean: clean
	@echo "$(YELLOW)Cleaning up all generated files...$(RESET)"
	@rm -f $(NAME) $(SYM_NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re