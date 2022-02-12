# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abittel <abittel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 10:24:03 by abittel           #+#    #+#              #
#    Updated: 2022/02/09 21:21:20 by abittel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	parsing2.c tab_manip.c lexer.c parser.c ft_treeadd_f.c ft_treenew.c ft_treeprof.c env_manager.c expander.c cd.c
OSRCS	=	${SRCS:.c=.o}
NAME_S	= minishell

all : ${NAME_S}

%.o: %.c 
	gcc -Wall -Werror -Wextra -c -I./libft -o $@ $< -g
${NAME_S} :	${OSRCS} libft/libft.a 
	gcc ${OSRCS} -Llibft -lft -lreadline -o ${NAME_S} -g
libft/libft.a :
	$(MAKE) -C libft/ bonus
clean :
	rm -rf ${OSRCS}
	$(MAKE) -C libft/ $@
fclean : clean
	rm -rf ${NAME_S}
	$(MAKE) -C libft/ $@
re : fclean all
.PHONY: all clean fclean re
