#include "ft_printf.h"
#include <libft.h>

t_flags		*flagsnew(t_flags *new)
{
	if (!new)
		if (!(new = ft_memalloc(sizeof(t_flags))))
			return (NULL);
	new->hash = 0;
	new->zero = 0;
	new->min = 0;
	new->space = 0;
	new->plus = 0;
	new->apos = 0;
	return (new);
}

t_conv		*convnew(t_conv *new)
{
	if (!new)
		if (!(new = ft_memalloc(sizeof(t_conv))))
			return (NULL);
	new->flags = flagsnew(new->flags);
	new->id = 0;
	new->width = 0;
	new->preci = -1;
	new->len = NONE;
	new->type = 0;
	return (new);
}

t_env		*envnew(t_env *new, const char *format)
{
	if (!new)
		if (!(new = ft_memalloc(sizeof(t_env))))
			return (NULL);
	new->form = format;
	new->i = 0;
	new->j = 0;
	new->ret = 0;
	new->fd = 1;
	return (new);
}
