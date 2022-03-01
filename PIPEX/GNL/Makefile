 
FILES = get_next_line.c get_next_line_utils.c

OBJS = ${FILES:.c=.o}

NAME = libgnl.a

FLAGS = -Wall -Wextra -Werror

%.o:	%.c
	gcc -c ${FLAGS} -o $@ $<  

all:	${NAME}

${NAME}:${OBJS}
	ar rc ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
