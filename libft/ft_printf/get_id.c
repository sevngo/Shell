#include "ft_printf.h"

int				get_id(t_env *env)
{
	int			start;
	int			res;

	start = env->i;
	res = 0;
	while (ft_isdigit(env->form[env->i]))
		env->i++;
	if (env->form[env->i] == '$')
	{
		res = ft_atoi(&env->form[start]);
		env->i++;
	}
	else
		env->i = start;
	return (res);
}
