#include "ft_printf.h"

static char	*set_float_zero_preci(char *str, int i, t_env *env)
{
	if (env->conv->flags->hash)
		i++;
	str[i] = '\0';
	return (str);
}

static char	*set_float_preci(char *new, char *str, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!env->conv->preci)
		return (set_float_zero_preci(str, i, env));
	j = -1;
	while (str[i])
	{
		i++;
		j++;
	}
	if (j < env->conv->preci)
	{
		j = env->conv->preci - j;
		new = ft_strnew(i + j);
		new = ft_strcpy(new, str);
		while (j--)
			new = ft_strcat(new, "0");
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

static char	*set_nbr_preci(char *new, char *str, t_env *env)
{
	int		len;

	if (env->conv->flags->hash && env->conv->type == 'o' &&
			(env->conv->preci <= 0))
		env->conv->preci = ft_strlen(str) + 1;
	if (!ft_atoi(str) && !env->conv->preci)
		new = ft_strnew(0);
	else if ((len = (env->conv->preci - ft_strlen(str))) > 0)
	{
		new = ft_strnew(len + ft_strlen(str));
		while (len--)
			new[len] = '0';
		new = ft_strcat(new, str);
	}
	else
		return (str);
	ft_strdel(&str);
	return (new);
}

static char	*set_str_preci(char *new, char *str, t_env *env)
{
	if (env->conv->len == l && env->conv->preci > 0)
	{
		while (isbegwchar(str[env->conv->preci - 1]) ||
				(ismidwchar(str[env->conv->preci - 1]) &&
				ismidwchar(str[env->conv->preci])))
			env->conv->preci--;
	}
	new = ft_strndup(str, env->conv->preci);
	ft_strdel(&str);
	return (new);
}

char		*set_precision(char *str, t_env *env)
{
	char	*new;

	new = NULL;
	if (str && !ft_strchr("c%", env->conv->type))
	{
		if (ft_strchr("sr", env->conv->type) && env->conv->preci >= 0)
			return (set_str_preci(new, str, env));
		else if (ft_strchr("douxXpb", env->conv->type))
			return (set_nbr_preci(new, str, env));
		else if (ft_strchr("fF", env->conv->type))
			return (set_float_preci(new, str, env));
	}
	return (str);
}
