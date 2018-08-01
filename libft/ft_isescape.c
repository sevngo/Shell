int	ft_isescape(int c)
{
	if (c == '\a' || c == '\b' || c == '\f' || c == '\n' || c == '\r' ||
			c == '\t' || c == '\v' || c == '\e')
		return (1);
	return (0);
}
