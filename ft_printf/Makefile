NAME	= libftprintf.a
INC		= includes
HEADER	= ft_printf.h
LIBC	= ar rcs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

SRCS	= ft_printf.c ft_utils.c
OBJS	= ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c ${INC}/${HEADER}
	${CC} ${CFLAGS} -c $< -o $@ -I${INC}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re