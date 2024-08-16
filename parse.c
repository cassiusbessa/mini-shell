// nova struct

// PLANO B
typedef struct s_command
{
	struct s_command	*prev;
	char				*instruction;
	t_list				*args;
	char				*doc;
	char				*path;
	int					fd[2];
	struct s_command	*next;
}	t_command;


// MAIS LENTO
typedef struct s_token
{
    char    *word;
    enum_type type;
}

// Parser 
// Here_doc - feito
// Executor
// ENV
// Retorno de status