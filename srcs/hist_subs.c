#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Get lenght of the current substring to expand.
**	-------------------------------------------------------------------------- +
*/

static void	get_substr_size(char *input, int *size)
{
	(*size)++;
	while (input[*size] && ft_isspace(input[*size]) == FALSE)
	{
		if (input[*size] == '!' && (*size < 1 || input[*size - 1] != '!'))
			break ;
		if (*size > 0 && input[*size] == '!' && input[*size - 1] == '!')
		{
			(*size)++;
			break ;
		}
		if (ft_isalnum(input[*size]) == FALSE)
		{
			if (input[*size] != '-' || (*size > 0 && input[*size] == '-'
						&& input[*size - 1] != '!'))
				break ;
		}
		(*size)++;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Calls the accurate function, depending on which option is in the string.
**	-------------------------------------------------------------------------- +
*/

static int	hist_expn(char **input)
{
	char	*arg;
	int		arg_size;
	int		mode;

	if (!input || !*input)
		return (EXIT_SUCCESS);
	arg_size = 0;
	get_substr_size(input[0], &arg_size);
	if (!(arg = ft_strsub(input[0], 0, arg_size)))
		return (EXIT_FAILURE);
	if (arg[1] && ft_strisdigit(arg + 1))
		return (hist_nth(input, arg, arg_size));
	else if ((arg[1] && arg[1] == '-' && arg[2] && ft_strisdigit(arg + 2))
				|| ft_strcmp(arg, "!!") == 0)
	{
		mode = ft_strcmp(arg, "!!") == 0 ? BANG_DOUBLE : BANG_MINUS;
		return (hist_mth(input, arg, arg_size, mode));
	}
	else if (arg[1] && ft_strisalpha(arg + 1))
		return (hist_str(input, arg, arg_size));
	else
		return (hist_err(input, arg));
}

/*
**	-------------------------------------------------------------------------- +
**	Loop through the `input` to replace all occurences of `!' builtin.
**	-------------------------------------------------------------------------- +
*/

static int	hist_subs_loop_fret(char *str1, char *str2, int ret)
{
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (ret);
}

static int	hist_subs_loop(char **input, int ret, int *sw, int x)
{
	char	*str1;
	char	*str2;

	x = 0;
	while (x < (int)ft_strlen(input[0]) && input[0][x])
	{
		if (input[0][x] == '!' && (x < 1 || input[0][x - 1] != CH_BACKSLASH)
				&& is_squoted(input[0], x) == FALSE)
		{
			*sw = TRUE;
			if (!(str1 = ft_strsub(input[0], 0, x)))
				return (EXIT_FAILURE);
			if (!(str2 = ft_strsub(input[0], x, ft_strlen(input[0]) - x)))
				return (EXIT_FAILURE);
			get_substr_size(input[0], &x);
			if ((ret = hist_expn(&str2)) != EXIT_SUCCESS)
				return (hist_subs_loop_fret(str1, str2, ret));
			ft_strdel(&input[0]);
			if (!(input[0] = ft_strjoin_free(str1, str2, 2)))
				return (EXIT_FAILURE);
		}
		else
			x++;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Will substitute given `input` with history entries, following `!' builtin
**	rules. Handles following options (anywhere in the string):
**	!n
**	!-n
**	!!
**	!string
**
**	Return EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

int			hist_subs(char **input)
{
	int	ret;
	int	sw;

	sw = FALSE;
	ret = EXIT_FAILURE;
	if (!ft_strchr(input[0], '!'))
		return (EXIT_SUCCESS);
	if ((ret = hist_subs_loop(input, ret, &sw, 0)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ret == 2)
	{
		ft_strdel(&input[0]);
		return (!(input[0] = ft_strnew(0)) ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	else if (sw == TRUE)
		ft_putendl_fd(input[0], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
