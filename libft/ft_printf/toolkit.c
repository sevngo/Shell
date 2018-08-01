#include "ft_printf.h"

int	istype(int c)
{
	if (ft_strchr("diouxXDOUfFCcSspnbBrw%", c) && c)
		return (1);
	return (0);
}

int	isflag(int c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+' || c == 39)
		return (1);
	return (0);
}

int	islenght(int c)
{
	if (ft_strchr("hljtzqL", c) && c)
		return (1);
	return (0);
}

int	ismidwchar(int c)
{
	if ((unsigned char)c >= 0x80 && (unsigned char)c <= 0xBF)
		return (1);
	return (0);
}

int	isbegwchar(int c)
{
	if ((unsigned char)c >= 0xC0 && (unsigned char)c <= 0xF7)
		return (1);
	return (0);
}
