#include "ft_printf.h"

void		goto_arg(va_list *ap, int id, t_env *env)
{
	int		j;

	j = 1;
	va_copy(*ap, env->beg);
	while (j < id)
	{
		va_arg(*ap, void*);
		j++;
	}
}
