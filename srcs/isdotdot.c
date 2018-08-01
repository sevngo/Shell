#include "../incs/minishell.h"

int	isdotdot(char *path)
{
	if (path && ft_strlen(path) >= 2 &&
			ft_strnequ(path, "..", 2) && (path[2] == '/' || !path[2]))
		return (1);
	return (0);
}
