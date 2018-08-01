#include "ft_printf.h"

static int		print(va_list *ap, t_env *env)
{
	while (env->form[env->i])
	{
		if (env->form[env->i] == '%')
		{
			env->conv = convnew(env->conv);
			get_conv(ap, env);
			if (env->conv->type)
			{
				if (conv_to_buffer(ap, env) == -1)
					return (-1);
				env->i++;
			}
		}
		else
			normal_to_buffer(env);
	}
	print_buffer(env);
	return (env->ret);
}

int				ft_printf(const char *format, ...)
{
	static t_env	*env = NULL;
	va_list			ap;
	int				tmp;

	tmp = 0;
	if (env && env->ret == -1)
		tmp = env->ret;
	if (!(env = envnew(env, format)))
		return (-1);
	va_start(ap, format);
	va_copy(env->beg, ap);
	env->ret = print(&ap, env);
	va_end(ap);
	if (tmp == -1)
		env->ret = -1;
	return (env->ret);
}
