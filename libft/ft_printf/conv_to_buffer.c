#include "ft_printf.h"

static int	change_fd(va_list *ap, t_env *env)
{
	print_buffer(env);
	env->fd = va_arg(*ap, int);
	if (env->fd < 0)
		return (-1);
	return (0);
}

static int	printed_to_ptr(va_list *ap, t_env *env)
{
	int		*ptr;

	ptr = va_arg(*ap, int*);
	*ptr = env->ret + env->j;
	return (0);
}

static char	*invalidespec(char *str, t_env *env)
{
	str = ft_strnew(1);
	str[0] = env->conv->type;
	env->conv->type = 'c';
	return (str);
}

static void	simplify_conv(t_conv *conv)
{
	if (conv->type == 'i')
		conv->type = 'd';
	if (ft_strchr("DOUCSpB", conv->type))
	{
		conv->type = ft_tolower(conv->type);
		conv->len = l;
	}
	if (conv->type == 'p')
		conv->flags->hash = 1;
	if (conv->flags->min || (ft_strchr("douxX", conv->type) &&
			conv->preci >= 0))
		conv->flags->zero = 0;
	if (!ft_strchr("dfF", conv->type))
	{
		conv->flags->plus = 0;
		conv->flags->space = 0;
	}
	if (!ft_strchr("oOxXpfF", conv->type))
		conv->flags->hash = 0;
	if (ft_strchr("fF", conv->type) && conv->preci == -1)
		conv->preci = 6;
}

int			conv_to_buffer(va_list *ap, t_env *env)
{
	char	*str;

	str = NULL;
	simplify_conv(env->conv);
	if (!istype(env->conv->type) || env->conv->type == '%')
		str = invalidespec(str, env);
	else if (ft_strchr("douxXpb", env->conv->type))
		str = nbr_to_str(ap, env);
	else if (ft_strchr("fF", env->conv->type))
		str = float_to_str(ap, env);
	else if (ft_strchr("csr", env->conv->type))
		str = chars_to_str(ap, env);
	else if (env->conv->type == 'n')
		return (printed_to_ptr(ap, env));
	else if (env->conv->type == 'w')
		return (change_fd(ap, env));
	if (!str)
		return (-1);
	return (putconv_to_buffer(str, env));
}
