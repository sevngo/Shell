#include "libft.h"

static char	*get_2wchar(char *str, wint_t wint)
{
	str[0] = (((wint & 0x07c0) >> 6) + 0xc0);
	str[1] = ((wint & 0x003F) + 0x80);
	return (str);
}

static char	*get_3wchar(char *str, wint_t wint)
{
	str[0] = (((wint & 0xF000) >> 12) + 0xE0);
	str[1] = (((wint & 0x0Fc0) >> 6) + 0x80);
	str[2] = ((wint & 0x003F) + 0x80);
	return (str);
}

static char	*get_4wchar(char *str, wint_t wint)
{
	str[0] = (((wint & 0x1c0000) >> 18) + 0xF0);
	str[1] = (((wint & 0x03F000) >> 12) + 0x80);
	str[2] = (((wint & 0x0Fc0) >> 6) + 0x80);
	str[3] = ((wint & 0x003F) + 0x80);
	return (str);
}

char		*ft_wchartoa(wint_t wint)
{
	char	*str;
	int		bn;

	bn = ft_wcharlen(wint);
	if (!bn)
		return (NULL);
	str = ft_strnew(bn);
	if (bn == 1)
		str[0] = wint;
	else if (bn == 2)
		str = get_2wchar(str, wint);
	else if (bn == 3)
		str = get_3wchar(str, wint);
	else if (bn == 4)
		str = get_4wchar(str, wint);
	return (str);
}
