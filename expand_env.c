#include "minishell.h"

static char *handle_null_env(t_part p, char *w);
static char *expand_env(t_hashmap *envs, char *key, t_part p, char *w);
static void expand_envs(t_hashmap *envs, t_token *t);
static char *handle_start_with_number_key(char *key, t_part p, char *w);

void  expand_all_envs(t_hashmap *envs, t_token_lst *lst)
{
  t_token *t;

  t = lst->head;
  while (t)
  {
    if (t->type == ARGUMMENT)
      expand_envs(envs, t);
    t = t->next;
  }
}

static char *expand_env(t_hashmap *envs, char *key, t_part p, char *w)
{
    char    *value;
    char    *expanded;
    int     i;
    int     j;

    if (ft_isdigit(key[0]))
        return (handle_start_with_number_key(key, p, w));
    value = get_value(envs, key);
    if (!value)
        return (handle_null_env(p, w));
    expanded = (char *)ft_calloc(ft_strlen(w) - (p.end - p.start) + ft_strlen(value), sizeof(char));
    j = 0;
    i = 0;
    while (i < p.start - 1)
    {
        expanded[i] = w[i];
        i++;
    }
    while (value[j])
        expanded[i++] = value[j++];
    while (w[p.end])
        expanded[i++] = w[p.end++];
    expanded[i] = '\0';
    return (expanded);
}

static void  expand_envs(t_hashmap *envs, t_token *t)
{

  char  *expanded;
  t_part  p;
  char  *key;

  p = find_env(t->word);
  if (p.start == p.end)
    return ;
  key = get_env_key(t->word, p);
  while (p.start != p.end)
  {
    expanded = expand_env(envs, key, p, t->word);
    free(key);
    free(t->word);
    t->word = expanded;
    p = find_env(t->word);
    if (p.start == p.end)
      break ;
    key = get_env_key(t->word, p);
  }
}

static char  *handle_null_env(t_part p, char *w)
{
  char  *expanded;
  int   i;

  expanded = (char *)ft_calloc(ft_strlen(w) - (p.end - p.start), sizeof(char));
  i = 0;
  while (i < p.start - 1)
  {
    expanded[i] = w[i];
    i++;
  }
  while (w[p.end])
    expanded[i++] = w[p.end++];
  expanded[i] = '\0';
  return (expanded);
}

static char *handle_start_with_number_key(char *key, t_part p, char *w)
{
    char    *expanded;
    int     i;
    int     j;

    expanded = (char *)ft_calloc(ft_strlen(w) - 1, sizeof(char));
    i = 0;
    while (i < p.start - 1)
    {
        expanded[i] = w[i];
        i++;
    }
    j = p.start + 1;
    while (w[j])
        expanded[i++] = w[j++];
    expanded[i] = '\0';
    return expanded;
}
