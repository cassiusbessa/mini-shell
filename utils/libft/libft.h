/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:15:46 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/22 19:58:38 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define TABLE_SIZE 100

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int						ft_islower(int c);
int						ft_isupper(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *nptr);
char					*ft_itoa(int n);
char					*ft_itoa_base(long n, int base);
char					*ft_utoa_base(unsigned long long n, int base);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
size_t					ft_strlen(const char *s);
char					*ft_strtrim(char const *s1, char const *set);
void					reverse(char *s, int len);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char const *s, char c);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strdup(const char *s);
void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
char					*get_next_line(int fd);
void					destroy_2d(void **array);

// list
// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_list;

// t_list		*ft_lstnew(void *content);
// void		ft_lstadd_front(t_list **lst, t_list *new);
// int			ft_lstsize(t_list *lst);
// t_list		*ft_lstlast(t_list *lst);
// void		ft_lstadd_back(t_list **lst, t_list *new);
// void		ft_lstdelone(t_list *lst, void (*del)(void *));
// void		ft_lstclear(t_list **lst, void (*del)(void*));
// void		ft_lstiter(t_list *lst, void (*f)(void *));
// t_list		*ft_lstmap(t_list *lst,
// 				void *(*f)(void *), void (*del)(void *));

// ft_print
int						ft_printf(const char *s, ...);
int						ft_putstr(char *s);
int						print_itoa(long n, int base, int upper);
int						print_pointer(void *p, int base);
int						prefix_pointer(void);
int						print_utoa(unsigned long long n, int base, int upper);

typedef struct s_key_value
{
	char				*key;
	char				*value;
	struct s_key_value	*next;
}						t_key_value;

void					destroy_pair(t_key_value *p);
t_key_value				*create_pair(const char *key, const char *value);
void					print_pair(t_key_value p);

typedef struct s_hashmap
{
	t_key_value			**table;
	int					size;
}						t_hashmap;

t_hashmap				*create_hash_map(void);
void					insert_pair(t_hashmap **map, t_key_value *p);
char					*get_value(t_hashmap *map, const char *key);
void					remove_key(t_hashmap **map, const char *key);
void					destroy_hashmap(t_hashmap *map);
void					print_hashmap(t_hashmap map);
unsigned int			hash(const char *key);

#endif
