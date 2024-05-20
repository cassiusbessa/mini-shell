# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 19:50:42 by caqueiro          #+#    #+#              #
#    Updated: 2024/05/20 18:07:01 by caqueiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

SRCS =		main.c\
			get_next_word.c\
			separators.c\
			list.c\
			command.c\
			command_list.c\
			exec_command.c\
			path.c\
			args.c\
			pipe.c\
			redirect.c\
			print.c

LIBFT = utils/libft/libft.a

MINISHELL = minishell

CC	= cc
RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

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
