FILES = heredoc.c parsing.c pipex.c manage_errors.c

OBJS = ${FILES:.c=.o}

NAME = libpipex.a

FLAGS = -Wall -Wextra -Werror

#LIBS = -ILIBFT/ -LLIBFT/ -lft -IGNL/ -LGNL/ -lgnl 

%.o:	%.c
	gcc -c ${FLAGS} -o $@ $<

all:	${NAME}

${NAME}:${OBJS}
	ar rc ${NAME} ${OBJS}
	${MAKE} -C ./LIBFT
	cp ./LIBFT/libft.a ${NAME}
	${MAKE} -C ./GNL
	cp ./GNL/libgnl.a ${NAME}
	gcc ${FLAGS} -o pipex ${OBJS}  GNL/libgnl.a LIBFT/libft.a

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}
	rm -f pipex

re:	fclean all

.PHONY:	all clean fclean re
