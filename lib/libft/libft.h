#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // read, fork, pipe, execve, macros 'STDERR_FILENO' etc.
# include <stddef.h> // size_t
# include <stdint.h> // SIZE_MAX
# include <stdarg.h> // variadic fcts
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef FD_SIZE
#  define FD_SIZE 1
# endif

/*
Used in libft functions for list manipulation.
- void *content:	This member is a pointer to the content stored in the node.
					The void pointer allows the structure to hold data of any
					type. Users of this structure can store any type of data by
					casting it to a void pointer before assigning it to
					this member.
- struct s_list *next:	This member is a pointer to the next node in the linked
						list. It allows the nodes to be linked together, forming
						a sequence. If a node is the last one in the list, this
						pointer will be NULL to indicate the end of the list.
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Core Functions

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*calloc(size_t nmemb, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

// Secondary Functions

char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Bonus Functions

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *));

//// Functions From Other Projects
// Just useful in general

int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi_base(const char *str, int str_base);

// Project: get_next_line

int		ft_isbinary(char *stash);
char	*get_next_line(int fd);

// Project: ft_printf

int		ft_printf(const char *format, ...);

// Project: ft_printf / utils

int		print_count_char(char _char);
int		print_count_string(char *str);
int		print_count_unsigned(unsigned int nbr);
int		print_count_number(int nbr);
int		print_count_hex(uintptr_t nbr, char format);

#endif
