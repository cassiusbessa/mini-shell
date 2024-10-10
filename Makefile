# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassius <cassius@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 19:50:42 by caqueiro          #+#    #+#              #
#    Updated: 2024/10/10 00:16:57 by cassius          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

SRCS =		main.c\
			exec_command.c\
			path.c\
			redirect.c\
			print.c\
			token_lst.c\
			token.c\
			token_type.c\
			parser.c\
			quotes.c\
			env.c\
			args.c\
			get_env_key.c\
			expand_env.c\
			signal.c


LIBFT = utils/libft/libft.a

MINISHELL = minishell

CC	= cc -g
RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -ggdb3 -g

OBJS	= ${SRCS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(MINISHELL):
		@make -C utils/libft
		${CC} ${SRCS} ${LIBFT} -o ${MINISHELL} -lreadline
		@printf "$(GREEN)    - Executable ready.\n$(RESET)"

all: $(MINISHELL)


clean:
		@make fclean -C utils/libft
		${RM} ${OBJS}
		@printf "$(YELLOW)    - Objects removed.$(RESET)\n"

fclean: clean
	${RM} ${MINISHELL}
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re:	fclean all
	@make fclean -C utils/libft
	${RM} ${OBJS}
	@printf "$(YELLOW)    - Objects removed.$(RESET)\n"
	@printf "$(GREEN)    - Makefile recompiled.$(RESET)\n"

.PHONY:	all clean fclean re

shit: re
	  clear
	  ./minishell