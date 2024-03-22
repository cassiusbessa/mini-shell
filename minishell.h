/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:30:36 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/21 21:21:27 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>




char *get_next_word(char **input);

typedef struct	s_node
{
	char			*value;
	struct s_node	*next;
}	t_node;

t_node	*new_node(char *value);

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;	
}	t_list;

t_list	*new_lst(void);
void	add_back(t_node *n, t_list **lst);

typedef struct s_command
{
	char				*instruction;
	t_list				*flags;
	char				*args;
	struct s_command	*next;
	char				*separator;
}	t_command;

t_command	*build_command(char **input);



#endif