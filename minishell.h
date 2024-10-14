/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:30:36 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/14 20:38:51 by cassius          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/ioctl.h>
# define CH_SEP "&><|!();"


char	*get_next_token(char *input);

void	print_double_pointer(char **arr);

typedef enum e_word_type {

	UNKNOWN = 0, //
	PIPE = 1, //
	REDIR_OUT = 2, //
	REDIR_IN = 3, //
	HERE_DOC = 4, //
	APPEND = 5, //
	COMMAND = 6,
	DOCUMENT = 7, //
	HERE_DOC_EOF = 8, //
	ARGUMMENT = 9
} t_word_type;

typedef struct s_token
{
	struct	s_token	*prev;
	char			*word;
	t_word_type		type;
	int				fd[2];
  int       piped;
	struct	s_token	*next;

} t_token;

t_token	*new_token(char *word);
char	*absolute_path(t_token *cmd, t_hashmap *envs);

typedef struct s_token_lst
{
	t_token	*head;
	t_token	*tail;
}	t_token_lst;


t_token_lst *new_token_lst(void);
void    	add_token(t_token *token, t_token_lst **lst);
void		print_token_lst(t_token_lst *lst);
void		destroy_token_lst(t_token_lst **lst);
void    	type_tokens(t_token_lst *lst);
int 		sintax_validation(t_token_lst lst);
int 		validate_quotes(char *w);
void    unquotes_all_words(t_token_lst *lst);
void		exec_all_commands(t_token_lst *lst, t_hashmap *envs);
void    consume_token(t_token_lst *lst, t_token *t);

t_hashmap   *build_envs(char **envp);
char    	**to_envp(t_hashmap map);

typedef struct s_part
{
	int	start;
	int	end;
}	t_part;

t_part	find_env(char *w);
char    *get_env_key(char *w, t_part p);
void	expand_all_envs(t_hashmap *envs, t_token_lst *lst);

char  **build_args(t_token_lst l);
void pipe_next_cmd(t_token_lst *lst);
void redir_next_cmd(t_token_lst *lst);
void  close_not_used_fd(t_token *t);
void  pipe_all_cmds(t_token_lst *lst);
void	redir_all_cmds(t_token_lst *lst);


void	setup_sigaction_handler(void);
void	setup_sigaction_child(void);


#endif