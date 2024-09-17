#include "minishell.h"

static int    skip_quote2(const char *str, int *i);

static void    skip_spaces2(const char *str, int *i);

char    *get_next_token2(char *input)
{
    static char			*cmp;
    static t_part		part;
    char                *token_str;

    if (!input || !cmp || cmp != input)
    {
		cmp = input;
		ft_memset(&part, 0, sizeof(part));
    }
	if (!input)
		return (NULL);
    // pular espaços
    skip_spaces2(input, &part.start);
    part.end = part.start;
    
    // andar até encontrar um caracter de "finalização"
    while (*(input + part.end) && (!ft_strchr(" \t\n<>|", *(input + part.end))))
        if (!skip_quote2(input, &part.end))
            part.end++;
            
    // caso encontre '<', '>', '|'
    if (part.end == part.start && *(input + part.start))
    {
        if (ft_strchr("<>", *(input + part.end)) && *(input + part.end) == *(input + part.end + 1))
            part.end++;
        part.end++;
    }
        
    // Pegar nova string
    token_str = ft_substr(input, part.start, (part.end - part.start));
    
    // Caso encontre string vazia (final da string)
    if (part.start == part.end)
        free(token_str);
    if (part.start == part.end)
        token_str = NULL;

    // Atualizar start para quando chamar de novo
    part.start = part.end;
    return (token_str);
}

static int    skip_quote2(const char *str, int *i)
{
    char    quote;

    if (!str || ((*(str + *i) != '\'') && (*(str + *i) != '"')))
        return (0);
    quote = *(str + *i);
    *i += 1;
    while (*(str + *i) && (*(str + *i) != quote))
        *i += 1;
    if (*(str + *i))
        *i += 1;
    return (1);
}

static void    skip_spaces2(const char *str, int *i)
{
    if (!str)
        return ;
    while (*(str + *i) && ft_strchr(" \n\t\r\f\v", *(str + *i)))
        *i += 1;
}