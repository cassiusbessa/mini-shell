/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:20:05 by caqueiro          #+#    #+#             */
/*   Updated: 2024/01/31 22:38:51 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

static int	find_line_break(t_list *lst)
{
	t_list	*current;
	char	*content;

	if (!lst)
		return (0);
	current = lst;
	content = current->content;
	while (current)
	{
		content = current->content;
		while (content && *content)
		{
			if (*content == '\n')
				return (1);
			content++;
		}
		current = current->next;
	}
	return (0);
}

static void	clean_list(t_list **lst)
{
	t_list	*current;
	size_t	i;
	char	*line;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current->next)
	{
		*lst = current->next;
		free(current->content);
		free(current);
		current = *lst;
	}
	i = 0;
	while (current->content[i] != '\n' && current->content[i])
		i++;
	line = ft_substr(current->content, i + 1,
			ft_strlen(current->content) - i);
	free((*lst)->content);
	(*lst)->content = line;
}

static char	*build_line(t_list **lst, char *line, int i, int j)
{
	t_list	*current;
	t_list	*temp;

	current = *lst;
	while (current)
	{
		temp = current->next;
		i = 0;
		while (current->content && current->content[i])
		{
			if (current->content[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return (line);
			}
			line[j++] = current->content[i++];
		}
		current = temp;
	}
	line[j] = '\0';
	return (line);
}

static char	*get_line(t_list **lst)
{
	char	*line;

	line = malloc(sizeof (char) * line_len(*lst) + 1);
	if (!line)
		return (NULL);
	if (!lst || !(*lst) || !(*lst)->content)
		return (NULL);
	line = build_line(lst, line, 0, 0);
	clean_list(lst);
	if (!*line)
	{
		free(line);
		free_list(lst);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*list[MAX_FD];
	char			*buffer_line;
	int				count_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	count_read = 1;
	while (!find_line_break(list[fd]) && count_read)
	{
		buffer_line = (char *)malloc(sizeof (char) * BUFFER_SIZE + 1);
		if (!buffer_line)
		{
			free_list(&list[fd]);
			return (NULL);
		}
		count_read = read(fd, buffer_line, BUFFER_SIZE);
		if (count_read < 0)
		{
			free(buffer_line);
			return (NULL);
		}
		buffer_line[count_read] = '\0';
		ft_lstadd_back(&list[fd], buffer_line);
	}
	return (get_line(&list[fd]));
}

/*#include <fcntl.h>
int main()
{
    int fd = open("big_line_with_nl", O_RDONLY);
    char *a = get_next_line(fd);
    printf("primeira chamada: %s", a);
    free(a);

    char *b = get_next_line(fd);
    printf("segunda chamada: %s", b);
    free(b);

    char *c = get_next_line(fd);
    printf("terceira chamada: %s", c);
    free(c);

    char *d = get_next_line(fd);
    printf("quarta chamada: %s", d);
    free(d);

    char *e = get_next_line(fd);
    printf("5 chamada: %s", e);
    free(e);

    char *f = get_next_line(fd);
    printf("6 chamada: %s", f);
    free(f);

    char *g = get_next_line(fd);
    printf("7 chamada: %s", g);
    free(g);

    char *h = get_next_line(fd);
    printf("8 chamada: %s", h);
    free(h);

    char *i = get_next_line(fd);
    printf("9 chamada: %s", i);
    free(i);

    char *j = get_next_line(fd);
    printf("10 chamada: %s", j);
    free(j);

    char *k = get_next_line(fd);
    printf("11 chamada: %s", k);
    free(k);

    char *l = get_next_line(fd);
    printf("12 chamada: %s", l);
    free(l);

    char *m = get_next_line(fd);
    printf("13 chamada: %s", m);
    free(m);

    char *n = get_next_line(fd);
    printf("décima quinta chamada: %s", n);
    free(n);

    char *o = get_next_line(fd);
    printf("14 chamada: %s", o);
    free(o);

    close(fd);

    return 0;
}*/
