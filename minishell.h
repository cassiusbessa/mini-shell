/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:30:36 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/22 15:50:53 by caqueiro         ###   ########.fr       */
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



/**
 * @brief Extracts the next word from a string and updates the input pointer.
 *
 * This function extracts the next word from the string pointed to by the input pointer.
 * It modifies the input pointer to point to the character following the extracted word.
 *
 * @param input Pointer to a pointer to the input string.
 * @return A pointer to the extracted word, or NULL if no word is found or if the input is NULL.
 */
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
	t_list				*args;
	struct s_command	*next;
	char				*separator;
}	t_command;

/**
 * @brief Constructs and initializes a command structure.
 *
 * This function creates and initializes a command structure representing a command with
 * instruction, flags, arguments, a separator, and a reference to the next command.
 *
 * @param input Pointer to a string containing the command data.
 * @return A pointer to the newly created command structure, or NULL on error.
 */
t_command	*build_command(char **input);

typedef struct s_cmd_lst
{
	t_command	*head;
	t_command	*tail;
}	t_cmd_lst;




void		add_command(t_command *cmd, t_cmd_lst *new_cmd);



#endif