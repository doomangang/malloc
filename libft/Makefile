# --- Colors for fancy output ---
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

NAME 	= libft.a
INC		= includes
HEADER	= libft.h
LIBC	= ar rcs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

SRCS	= ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c
SRCS_B	= ft_lstadd_front_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstmap_bonus.c \
    	ft_lstclear_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstiter_bonus.c
OBJS	= ${SRCS:.c=.o}
OBJS_B  = ${SRCS_B:.c=.o}

ifdef WITH_BONUS
	OBJ_SWITCH = ${OBJS} ${OBJS_B}
else
	OBJ_SWITCH = ${OBJS}
endif

all: ${NAME}

bonus:
	@${MAKE} WITH_BONUS=1 all

${NAME}: ${OBJ_SWITCH}
	@echo "$(BLUE)Archiving object files into $(NAME)...$(RESET)"
	@${LIBC} $@ $^
	@echo "$(GREEN)✓ libft.a successfully created!$(RESET)"

%.o: %.c
	@printf "$(BLUE)Compiling libft source: %-30s$(RESET)\r" $<
	@${CC} ${CFLAGS} -c $< -o $@ -I${INC}

clean:
	@echo "$(BLUE)Cleaning libft object files...$(RESET)"
	@${RM} ${OBJS} ${OBJS_B}

fclean: clean
	@echo "$(BLUE)Cleaning up libft library file...$(RESET)"
	@${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re bonus