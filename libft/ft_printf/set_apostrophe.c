#include "ft_printf.h"

static char	*setapos_to_intpart(char *str, t_env *env)
{
	char	*new;
	int		i;
	int		j;
	int		k;
	int		width;

	i = ft_strlen(str);
	width = (env->conv->type != 'b' ? 3 : 4);
	k = i % width;
	j = i / width - (!k ? 1 : 0);
	if (!(new = ft_strnew(i + j)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		new[j++] = str[i++];
		if (((!--k || (k < 0 && !((k * -1) % width))) && str[i]))
			new[j++] = ',';
	}
	return (new);
}

char		*set_apostrophe(char *str, t_env *env)
{
	char	*new;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	new = NULL;
	if (ft_strchr("fF", env->conv->type) && ft_strchr(str, '.'))
	{
		while (str[i] && str[i] != '.')
			i++;
		if ((tmp1 = ft_strsub(str, 0, i)))
		{
			if ((tmp2 = setapos_to_intpart(tmp1, env)))
			{
				new = ft_strjoin(tmp2, &str[i]);
				ft_strdel(&tmp2);
			}
			ft_strdel(&tmp1);
		}
	}
	else
		new = setapos_to_intpart(str, env);
	ft_strdel(&str);
	return (new);
}
