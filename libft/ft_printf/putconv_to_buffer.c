#include "ft_printf.h"

static void		hash_to_buffer(t_env *env)
{
	if (env->conv->flags->hash)
		if (ft_strchr("xXp", env->conv->type))
		{
			if (env->conv->type == 'X')
				putstr_to_buffer("0X", env);
			else
				putstr_to_buffer("0x", env);
		}
}

static void		sign_to_buffer(t_env *env)
{
	if (env->conv->flags->plus == 1)
		putchar_to_buffer('+', env);
	else if (env->conv->flags->plus == -1)
		putchar_to_buffer('-', env);
	else if (env->conv->flags->space)
		putchar_to_buffer(' ', env);
}

static void		padding_to_buffer(int len, char c, t_env *env)
{
	while (len-- > 0)
		putchar_to_buffer(c, env);
}

static int		getpaddinglen(char *str, t_env *env)
{
	int			len;

	len = 0;
	len = ft_strlen(str);
	if (!str[0] && env->conv->type == 'c')
		len++;
	if (env->conv->preci > len && len > env->conv->width)
		len = env->conv->preci;
	if (env->conv->flags->plus || env->conv->flags->space)
		len++;
	if (env->conv->flags->hash && ft_strchr("xXp", env->conv->type))
		len += 2;
	if (env->conv->width > len)
		return (env->conv->width - len);
	return (0);
}

int				putconv_to_buffer(char *str, t_env *env)
{
	int			padlen;

	if (env->conv->flags->apos && ft_strchr("dubfF", env->conv->type) && str)
		str = set_apostrophe(str, env);
	str = set_precision(str, env);
	if (!str)
		return (-1);
	padlen = getpaddinglen(str, env);
	if (!env->conv->flags->zero && !env->conv->flags->min && padlen)
		padding_to_buffer(padlen, ' ', env);
	hash_to_buffer(env);
	sign_to_buffer(env);
	if (env->conv->flags->zero)
		padding_to_buffer(padlen, '0', env);
	if (ft_strchr("xp", env->conv->type))
		str = ft_strlowcase(str);
	if (env->conv->type == 'c' && (!str[0] || env->conv->len != l))
		putchar_to_buffer(str[0], env);
	else
		putstr_to_buffer(str, env);
	if (!env->conv->flags->zero && env->conv->flags->min)
		padding_to_buffer(padlen, ' ', env);
	ft_strdel(&str);
	return (0);
}
