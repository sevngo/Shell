#include "ft_printf.h"

static double	cast_float_nbr(va_list *ap, t_conv *conv)
{
	if (conv->len == L)
		return (va_arg(*ap, long double));
	else
		return (va_arg(*ap, double));
}

char			*float_to_str(va_list *ap, t_env *env)
{
	long double	nbr;
	char		*new;

	nbr = cast_float_nbr(ap, env->conv);
	if (nbr < 0)
	{
		nbr = -nbr;
		env->conv->flags->plus = -1;
	}
	new = ft_ftoa(nbr, env->conv->preci);
	return (new);
}
