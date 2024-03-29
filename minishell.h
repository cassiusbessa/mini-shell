/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:30:36 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/29 20:17:19 by caqueiro         ###   ########.fr       */
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
# define CH_SEP "&><|!();"

/**
 * @brief Extracts the next word from a string and updates the input pointer.
 *
 * Function extracts the next word from the string pointed to by the input.
 * It modifies the input pointer to the next character of the extracted word.
 *
 * @param input Pointer to a pointer to the input string.
 * @return A pointer to the extracted word.
 */
char		*get_next_word(char **input);

/**
 * @brief Finds the index position of the last character separator.
 *
 * This function searches for the last occurrence of any character
 * separator in the input string pointed to by the input
 *
 * @param input Pointer to a pointer to the input string.
 * @return The index position of the last character separator found,
 *         or -1 if no separator is found.
 */
int	find_separators(char *input);

int	find_first_separator(char *input);

typedef struct	s_node
{
	char			*value;
	struct s_node	*next;
}	t_node;

t_node		*new_node(char *value);

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;	
}	t_list;

t_list	*new_lst(void);
void		add_back(t_node *n, t_list **lst);
void    destroy_list(t_list *lst);
void		print_list(t_list *lst);

typedef struct s_command
{
	char				*instruction;
	t_list				*flags;
	t_list				*args;
	char				*separator;
	struct s_command	*next;
}	t_command;

t_command	*build_command(char **input);

typedef struct s_cmd_lst
{
	t_command	*head;
	t_command	*tail;
}	t_cmd_lst;

t_cmd_lst *new_cmd_lst(void);
void		  add_cmd(t_command *cmd, t_cmd_lst **lst);
void      destroy_cmd_lst(t_cmd_lst *lst);
void 			print_all_commands(t_cmd_lst *lst);

#endif