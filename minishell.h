/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:30:36 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/06 20:30:27 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils/libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>
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

char *get_next_token(char **input);

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
int		find_separators(char *input);

int		find_first_separator(char *input);

typedef struct	s_node
{
	void			*value;
	struct s_node	*next;
}	t_node;

t_node		*new_node(char *value);

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	size_t	size;
}	t_list;

t_list	*new_lst(void);
void		add_back(t_node *n, t_list **lst);
void    destroy_list(t_list *lst);
void	print_list(t_list *lst);
void	print_double_pointer(char **arr);
t_list	*copy_lst(t_list *lst);

typedef enum e_word_type {

	UNKNOWN = 0,
	PIPE = 1,
	REDIR_OUT = 2,
	REDIR_IN = 3,
	HERE_DOC = 4,
	APPEND = 5,
	COMMAND = 6,
	DOCUMENT = 7,
	HERE_DOC_EOF = 8,
	ARGUMMENT = 9
} t_word_type;

typedef struct s_token
{
	struct	s_token	*prev;
	char			*word;
	t_word_type		type;
	int				fd[2];
	struct	s_token	*next;

} t_token;

t_token	*new_token(char *word);

typedef struct s_token_lst
{
	t_token	*head;
	t_token	*tail;
}	t_token_lst;

t_token_lst *new_token_lst(void);
void    	add_token(t_token *token, t_token_lst **lst);
void		print_token_lst(t_token_lst *lst);
void		destroy_token_lst(t_token_lst **lst);
void    type_specials_token(t_token_lst *lst);




typedef struct s_command
{
	struct s_command	*prev;
	char				*instruction;
	t_list				*flags;
	t_list				*args;
	char				*separator;
	char				*doc;
	char				*path;
	int					fd[2];
	struct s_command	*next;
}	t_command;


void		set_cmd_path(t_command *cmd);
t_command	*build_command(char **input);
char		**list_to_args(t_command *lst);
int	check_separator(char *sep, t_command *cmd);

typedef struct s_cmd_lst
{
	t_command	*head;
	t_command	*tail;
}	t_cmd_lst;

t_cmd_lst *new_cmd_lst(void);
void		  add_cmd(t_command *cmd, t_cmd_lst **lst);
void      destroy_cmd_lst(t_cmd_lst **lst);
void		print_command(t_command *cmd);
void 			print_all_commands(t_cmd_lst *lst);
void		exec_all_commands(t_cmd_lst *lst);
// void		exec_command(t_command *cmd);



void	handle_pipe(t_command **cmd);
void		handle_output_redirect(t_command **cmd);
// void	handle_input_redirect(t_command **cmd);
// int 	here_doc_redirect(t_command *cmd, char *eof);

#endif