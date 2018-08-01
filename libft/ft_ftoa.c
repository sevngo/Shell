#include <libft.h>

static char	*ftoa_fix(int preci, int len, char *tmp)
{
	char	*new;

	if (!(new = ft_strnew(preci)))
		return (NULL);
	while (--len)
		new[len] = '0';
	new = ft_strcat(new, tmp);
	ft_strdel(&tmp);
	return (new);
}

char		*ft_ftoa(long double nbr, int preci)
{
	char	*new;
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = ft_itoa_base((uintmax_t)nbr, 10);
	nbr = nbr - ((uintmax_t)nbr);
	tmp2 = ft_itoa_base((((nbr) * ft_recursive_power(10, preci)) + 0.5), 10);
	i = ft_strlen(tmp2);
	if ((i = preci - i) > 0)
		tmp2 = ftoa_fix(preci, i, tmp2);
	if (!tmp1 || !tmp2)
		return (NULL);
	new = ft_strnew(ft_strlen(tmp1) + ft_strlen(tmp2) + 1);
	new = ft_strcpy(new, tmp1);
	new = ft_strcat(new, ".");
	new = ft_strcat(new, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (new);
}
