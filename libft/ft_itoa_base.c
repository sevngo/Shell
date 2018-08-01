#include <libft.h>

static int	ft_nbrlen_base(uintmax_t n, int base)
{
	int		i;

	i = 1;
	while (n >= (uintmax_t)base)
	{
		n /= base;
		++i;
	}
	return (i);
}

char		*ft_itoa_base(uintmax_t n, int base)
{
	int		nbrlen;
	char	*str;

	nbrlen = ft_nbrlen_base(n, base);
	if (!(str = ft_memalloc(sizeof(char) * (nbrlen + 1))))
		return (NULL);
	str[nbrlen] = '\0';
	while (nbrlen--)
	{
		if (n % base < 10)
			str[nbrlen] = n % base + 48;
		else
			str[nbrlen] = n % base + 55;
		n /= base;
	}
	return (str);
}
