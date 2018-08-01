#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft.h>
# include <stdarg.h>

typedef enum	e_lenght
{
	NONE, hh, h, l, ll, j, t, z, q, L
}				t_lenght;

typedef struct	s_flags
{
	int			hash;
	int			zero;
	int			min;
	int			space;
	int			plus;
	int			apos;
}				t_flags;

typedef struct	s_conv
{
	t_flags		*flags;
	int			width;
	int			preci;
	t_lenght	len;
	char		type;
	int			id;
	void		*ptr;
}				t_conv;

typedef struct	s_env
{
	const char	*form;
	int			i;
	char		buf[BUFF_SIZE];
	int			j;
	va_list		beg;
	t_conv		*conv;
	int			ret;
	int			fd;
}				t_env;

/*
** MAIN
*/

void			get_conv(va_list *ap, t_env *env);
int				conv_to_buffer(va_list *ap, t_env *env);
void			normal_to_buffer(t_env *env);
void			goto_arg(va_list *ap, int id, t_env *env);

/*
** TO STR
*/

char			*nbr_to_str(va_list *ap, t_env *env);
char			*float_to_str(va_list *ap, t_env *env);
char			*chars_to_str(va_list *ap, t_env *env);

/*
** INIT
*/

t_flags			*flagsnew(t_flags *flags);
t_conv			*convnew(t_conv *conv);
t_env			*envnew(t_env *env, const char *format);

/*
** CONV GETTERS
*/

int				get_id(t_env *env);

/*
** FORMATING
*/

int				putconv_to_buffer(char *str, t_env *env);
char			*set_precision(char *str, t_env *env);
char			*set_apostrophe(char *str, t_env *env);

/*
** BUFFERING
*/

void			print_buffer(t_env *env);
void			putchar_to_buffer(char c, t_env *env);
void			putstr_to_buffer(char *str, t_env *env);

/*
**	TOOLKIT
*/

int				isconv(int c);
int				istype(int c);
int				isflag(int c);
int				islenght(int c);
int				ismidwchar(int c);
int				isbegwchar(int c);

#endif
