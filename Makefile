# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abittel <abittel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 10:24:03 by abittel           #+#    #+#              #
#    Updated: 2022/03/05 20:45:12 by abittel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS = main.c exec/get_pwd.c exec/build_in.c exec/cd.c exec/echo.c exec/env.c exec/env_manager.c exec/env_utils.c exec/exec_cmd.c exec/exit.c exec/export.c exec/path_manager.c exec/pipes.c exec/pwd.c exec/read_heardoc.c exec/redir.c exec/unset.c parsing/expander.c parsing/expander_algo.c parsing/get_end.c parsing/init_free_cmd.c parsing/is_token.c parsing/lexer.c parsing/parse_cmd.c parsing/parser.c utils/blank_cmd.c utils/ft_treeadd_f.c utils/ft_treenew.c utils/ft_treeprof.c utils/str_utils.c utils/tab_free.c utils/tab_manip.c utils/tab_manip_str.c
OSRCS	=	${SRCS:.c=.o}
NAME_S	= minishell

all : ${NAME_S}

%.o: %.c 
	gcc -Wall -Werror -Wextra -c -I./include -I./libft -o $@ $< -g
${NAME_S} :	${OSRCS} libft/libft.a 
	gcc ${OSRCS} -Llibft -lft -lreadline -lncurses -o ${NAME_S} -g
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
