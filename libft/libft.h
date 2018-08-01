#ifndef LIBFT_H
# define LIBFT_H

/*
**	-------------------------------------------------------------------------- +
**	Includes
**	-------------------------------------------------------------------------- +
*/

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>

/*
**	-------------------------------------------------------------------------- +
**	Defines: ANSI colors
**	-------------------------------------------------------------------------- +
*/

# define C_RESET			"\033[0m"
# define C_BOLD_ON			"\033[1m"
# define C_ITALIC_ON		"\033[3m"
# define C_UNDERLINE_ON		"\033[4m"
# define C_INVERSE_ON		"\033[7m"
# define C_BOLD_OFF			"\033[22m"
# define C_ITALIC_OFF		"\033[23m"
# define C_UNDERLINE_OFF	"\033[24m"
# define C_INVERSE_OFF		"\033[27m"

# define FG_BLACK			"\033[30m"
# define FG_RED				"\033[31m"
# define FG_GREEN			"\033[32m"
# define FG_YELLOW			"\033[33m"
# define FG_BLUE			"\033[34m"
# define FG_MAGENTA			"\033[35m"
# define FG_CYAN			"\033[36m"
# define FG_WHITE			"\033[37m"
# define FG_RESET			"\033[39m"

# define BG_BLACK			"\033[40m"
# define BG_RED				"\033[41m"
# define BG_GREEN			"\033[42m"
# define BG_YELLOW			"\033[43m"
# define BG_BLUE			"\033[44m"
# define BG_MAGENTA			"\033[45m"
# define BG_CYAN			"\033[46m"
# define BG_WHITE			"\033[47m"
# define BG_RESET			"\033[49m"

/*
**	-------------------------------------------------------------------------- +
**	Structures, linked lists
**	-------------------------------------------------------------------------- +
*/

typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
**	-------------------------------------------------------------------------- +
**	Part 1 - Libc functions
**	-------------------------------------------------------------------------- +
*/

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void	*dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

/*
**	-------------------------------------------------------------------------- +
**	Part 2 - Additional functions
**	-------------------------------------------------------------------------- +
*/

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_separator(char *prefix, char *suffix,
										char *separator, int f);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putchar_nb_fd(int fd, char c, int size);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
**	-------------------------------------------------------------------------- +
**	Part 3 - Bonus functions
**	-------------------------------------------------------------------------- +
*/

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
**	-------------------------------------------------------------------------- +
**	Part 4 - Extra functions
**	-------------------------------------------------------------------------- +
*/

int				ft_nbofwords(char *s, char c);
size_t			ft_intlen(int n);
void			ft_check(void);
void			ft_free(void *ptr);
void			ft_putnbrnl(int n);
void			ft_putcharnl(char c);
char			**ft_arrdup(char **arr);
char			**ft_arrndup(char **arr, int size);
size_t			ft_arrlen(char **arr);
void			ft_arrfree(char **arr);
void			ft_arrrev(char **arr);
void			ft_arrsort(char **arr);
void			ft_arrprint(char **tab, char c);
int				ft_countc(char *str, char c);
int				ft_getch(void);
void			ft_putarr(char **arr);
void			ft_putcolor(char *s, char *color);
char			*ft_strjoin_free(char *s1, char *s2, int mode);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strnjoin(char const *s1, char const *s2, size_t n);
char			*ft_strrcpy(char *dst, const char *src, size_t start);
char			*ft_strrdup(const char *s1, size_t start);
int				ft_isspace(int c);
int				ft_strisblank(char *str);
int				ft_strisdigit(char *str);
int				ft_strisalpha(char *str);
char			*ft_strepart(char *str, char *rep, int st, int sp);
int				ft_printf(const char *format, ...);
int				ft_isescape(int c);
char			*ft_wchartoa(wint_t wint);
char			*ft_wstrtoa(wchar_t *wstr);
int				ft_wstrlen(wchar_t *wstr);
int				ft_wcharlen(wint_t wint);
void			ft_tabdel(char ***atab);
char			*ft_ftoa(long double nbr, int preci);
char			*ft_itoa_base(uintmax_t n, int base);
char			*ft_strlowcase(char *s);
intmax_t		ft_recursive_power(intmax_t nb, int power);
char			*ft_strcjoin(char const *s1, char const *s2, char c);

/*
**	-------------------------------------------------------------------------- +
**	Macro & linked list for get_next_line()
**	-------------------------------------------------------------------------- +
*/

# define BUFF_SIZE	64

typedef struct	s_mfd
{
	int				fd;
	char			*mem;
	struct s_mfd	*next;
}				t_mfd;

int				get_next_line(const int fd, char **line);

#endif
