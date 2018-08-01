#ifndef intmax_t
# include <stdint.h>
#endif
#include <stdlib.h>

intmax_t	ft_recursive_power(intmax_t nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}
