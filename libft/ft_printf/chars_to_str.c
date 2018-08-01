#include "ft_printf.h"

static char			get_escapechar(int c)
{
	if (c == '\a')
		return ('a');
	else if (c == '\b')
		return ('b');
	else if (c == '\f')
		return ('f');
	else if (c == '\n')
		return ('n');
	else if (c == '\r')
		return ('r');
	else if (c == '\t')
		return ('t');
	else if (c == '\v')
		return ('v');
	else if (c == '\e')
		return ('e');
	return (0);
}

static char			*get_escapestr(char *str)
{
	char			*new;
	int				i;
	int				n;

	i = -1;
	n = 0;
	while (str[++i])
		n = (ft_isescape(str[i]) ? n + 1 : n);
	if (!n)
		return (str);
	new = ft_strnew(i + n);
	i = -1;
	n = 0;
	while (str[++i])
	{
		if (ft_isescape(str[i]))
		{
			new[i + ++n - 1] = '\\';
			new[i + n] = get_escapechar(str[i]);
		}
		else
			new[i + n] = str[i];
	}
	ft_strdel(&str);
	return (new);
}

static char			*get_wstr(va_list *ap)
{
	char			*new;
	wchar_t			*tmp;

	if (!(tmp = va_arg(*ap, wchar_t*)))
		new = ft_strdup("(null)");
	else
		new = ft_wstrtoa(tmp);
	return (new);
}

static char			*get_str(va_list *ap)
{
	char	*new;

	if (!(new = va_arg(*ap, char*)))
		new = ft_strdup("(null)");
	else
		new = ft_strdup(new);
	return (new);
}

char				*chars_to_str(va_list *ap, t_env *env)
{
	char			*new;
	unsigned int	c;

	new = NULL;
	if (ft_strchr("sr", env->conv->type))
	{
		if (env->conv->len != l)
			new = get_str(ap);
		else
			new = get_wstr(ap);
		if (new && env->conv->type == 'r')
			new = get_escapestr(new);
	}
	else
	{
		c = va_arg(*ap, unsigned int);
		if (env->conv->len != l)
		{
			new = ft_strnew(1);
			new[0] = c;
		}
		else
			new = ft_wchartoa(c);
	}
	return (new);
}
