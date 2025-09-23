# --- Colors for fancy output ---
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

NAME_BASE = libft_malloc
# HOSTTYPE 환경 변수 확인 및 설정 (과제 요구사항)
ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)-$(shell uname -s)
endif

NAME = $(NAME_BASE)_$(HOSTTYPE).so
SYM_NAME = libft_malloc.so

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/malloc.c
OBJS = $(SRCS:.c=.o)

# libft 라이브러리 경로
LIBFT_A = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

# 최종 공유 라이브러리 생성 규칙
$(NAME): $(LIBFT_A) $(OBJS)
	@echo "$(YELLOW)Linking object files to create shared library: $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) -Llibft -lft
	@echo "$(YELLOW)Creating symbolic link: $(SYM_NAME) -> $(NAME)...$(RESET)"
	@ln -sf $(NAME) $(SYM_NAME)
	@echo "$(GREEN)✓ Malloc library successfully created!$(RESET)"

# libft.a 파일이 필요할 때 libft 폴더의 make를 실행
$(LIBFT_A):
	@echo "$(YELLOW)Building dependency: libft.a...$(RESET)"
	@make -C libft

# malloc.c 컴파일 규칙 추가
%.o: %.c
	@echo "$(YELLOW)Compiling malloc source: $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc

clean:
	@echo "$(YELLOW)Cleaning malloc object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@echo "$(YELLOW)Cleaning up all generated files...$(RESET)"
	@rm -f $(NAME) $(SYM_NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re