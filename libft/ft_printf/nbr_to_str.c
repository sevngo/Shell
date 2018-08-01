#include "ft_printf.h"

static intmax_t		cast_signed_nbr(va_list *ap, t_conv *conv)
{
	if (conv->len == hh)
		return ((char)va_arg(*ap, int));
	else if (conv->len == h)
		return ((short)va_arg(*ap, int));
	else if (conv->len == l)
		return (va_arg(*ap, long));
	else if (conv->len == ll)
		return ((long long)va_arg(*ap, long));
	else if (conv->len == j)
		return (va_arg(*ap, intmax_t));
	else if (conv->len == z)
		return (va_arg(*ap, ssize_t));
	else
		return (va_arg(*ap, int));
}

static uintmax_t	cast_unsigned_nbr(va_list *ap, t_conv *conv)
{
	if (conv->len == hh)
		return ((unsigned char)va_arg(*ap, unsigned int));
	else if (conv->len == h)
		return ((unsigned short)va_arg(*ap, unsigned int));
	else if (conv->len == l)
		return (va_arg(*ap, unsigned long));
	else if (conv->len == ll)
		return (va_arg(*ap, unsigned long long));
	else if (conv->len == j)
		return (va_arg(*ap, uintmax_t));
	else if (conv->len == z)
		return (va_arg(*ap, size_t));
	else
		return (va_arg(*ap, unsigned int));
}

static void			null_nbr_fix(t_conv *conv)
{
	if (ft_strchr("xX", conv->type))
		conv->flags->hash = 0;
	if (conv->flags->hash && conv->type == 'o')
		conv->preci = 1;
}

char				*nbr_to_str(va_list *ap, t_env *env)
{
	char			*new;
	intmax_t		nbr;

	if (env->conv->type == 'd')
	{
		nbr = cast_signed_nbr(ap, env->conv);
		if (nbr < 0)
		{
			nbr = -nbr;
			env->conv->flags->plus = -1;
		}
	}
	else
		nbr = cast_unsigned_nbr(ap, env->conv);
	(!nbr ? null_nbr_fix(env->conv) : NULL);
	new = NULL;
	if (ft_strchr("du", env->conv->type))
		new = ft_itoa_base((uintmax_t)nbr, 10);
	else if (ft_strchr("oO", env->conv->type))
		new = ft_itoa_base((uintmax_t)nbr, 8);
	else if (ft_strchr("b", env->conv->type))
		new = ft_itoa_base((uintmax_t)nbr, 2);
	else if (ft_strchr("xXp", env->conv->type))
		new = ft_itoa_base((uintmax_t)nbr, 16);
	return (new);
}
