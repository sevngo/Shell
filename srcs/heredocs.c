#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Tells if the current `input` contains directly a heredoc, and if so, stores
**	its delimiter in `delimiter`.
**
**	Return values:
**	-1	- error
**	 0	- `input` can not be considered as a delimiter
**	 1	- `input` can be considered as a delimiter
**	-------------------------------------------------------------------------- +
*/

static int	h_next_del(char **delimiter, char *input)
{
	int	len;
	int	x;
	int	i;

	i = 0;
	if (input[i] && input[i++] != '<')
		return (0);
	if (input[i] && input[i++] != '<')
		return (0);
	while (input[i] && ft_isspace(input[i]))
		i++;
	x = i;
	len = 0;
	while (input[x] && ft_isalnum(input[x++]))
		len++;
	if (len == 0)
		return (0);
	if (!(*delimiter = ft_strnew(len)))
		return (-1);
	ft_strncpy(*delimiter, input + i, len);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Counts the number of heredocs in `input`.
**
**	Return values:
**	-1	- error
**	len	- the lenght of heredocs array
**	-------------------------------------------------------------------------- +
*/

static int	h_count(char *input)
{
	char	*delimiter;
	int		ret;
	int		len;
	int		i;

	i = 0;
	len = 0;
	delimiter = NULL;
	while (input[i])
	{
		if ((ret = h_next_del(&delimiter, input + i)) == -1)
			return (ret);
		else if (ret == 0)
			i++;
		else
		{
			i += ft_strlen(delimiter);
			ft_strdel(&delimiter);
			len++;
		}
	}
	return (len);
}

/*
**	-------------------------------------------------------------------------- +
**	When a new delimiter has been found, this function gets called and user is
**	asked to give input, until he enters EXACTLY a string matching `delimiter`.
**	-------------------------------------------------------------------------- +
*/

static int	h_fill_loop(char **heredocs, char *delimiter, int x)
{
	char	*tmp1;
	char	*tmp2;
	int		ret;

	tmp1 = NULL;
	tmp2 = NULL;
	sh_prompt(PROMPT_HDOCS);
	if ((ret = input_read(&tmp1, PROMPT_HDOCS)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ret == EXIT_CTRL_C)
	{
		ft_strdel(&tmp1);
		ft_strdel(&delimiter);
		return (EXIT_CTRL_C);
	}
	if (ret == EXIT_CTRL_D || ft_strcmp(tmp1, delimiter) == 0)
	{
		ft_strdel(&tmp1);
		return (21);
	}
	if (!(tmp2 = ft_strjoin_free(heredocs[x], "\n", 1)))
		return (EXIT_FAILURE);
	if (!(heredocs[x] = ft_strjoin_free(tmp2, tmp1, 2)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	h_fill(char **heredocs, char *delimiter, int x)
{
	int		ret;

	sh_prompt(PROMPT_HDOCS);
	if ((ret = input_read(&heredocs[x], PROMPT_HDOCS)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ret == EXIT_CTRL_C)
	{
		ft_strdel(&delimiter);
		return (EXIT_CTRL_C);
	}
	if (ret == EXIT_CTRL_D || ft_strcmp(heredocs[x], delimiter) == 0)
	{
		ft_strdel(&heredocs[x]);
		return (!(heredocs[x] = ft_strnew(0)) ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	while (21)
		if ((ret = h_fill_loop(heredocs, delimiter, x)) != EXIT_SUCCESS)
			return (ret == 21 ? EXIT_SUCCESS : ret);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Counts number of heredocs in `input`, allocates a container, and store
**	heredocs content in the correct order.
**	-------------------------------------------------------------------------- +
*/

int			handle_heredocs(char ***heredocs, char *input)
{
	char	*delimiter;
	int		ret;
	int		x;
	int		i;

	i = 0;
	if ((x = h_count(input)) == 0)
		return (EXIT_SUCCESS);
	if (!(*heredocs = ft_memalloc(sizeof(char *) * (x + 1))))
		return (EXIT_FAILURE);
	x = 0;
	while (input[i])
	{
		if ((ret = h_next_del(&delimiter, input + i)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 1)
		{
			if ((ret = h_fill(*heredocs, delimiter, x++)) != EXIT_SUCCESS)
				return (ret);
			i += ft_strlen(delimiter);
			ft_strdel(&delimiter);
		}
		i += (ret == 0 ? 1 : 0);
	}
	return (EXIT_SUCCESS);
}
