#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Check quotes formatting by iterating through the input until it matches a
**	quote (single, or double), keep the quote in memory, and iterate again until
**	it find the closing one.
**	Returns FALSE if a quote is missing in `input`.
**	-------------------------------------------------------------------------- +
*/

static int	input_check_quotes(const char *input)
{
	char	mem;
	int		i;

	i = 0;
	while (input[i])
	{
		if ((i == 0 || input[i - 1] != CH_BACKSLASH) &&
				(input[i] == CH_SQUOTE || input[i] == CH_DQUOTE))
		{
			mem = input[i++];
			while (input[i] && (input[i] != mem ||
					(mem == CH_DQUOTE &&
						(i != 0 && input[i - 1] == CH_BACKSLASH))))
				i++;
			if (!input[i] || input[i] != mem)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/*
**	-------------------------------------------------------------------------- +
**	Check backslash formatting by verifying if the last character is a backslash
**	(`\'), meaning it has no following character.
**	Returns FALSE if a character is missing after the backslash in `input`.
**	-------------------------------------------------------------------------- +
*/

static int	input_check_operators(const char *input)
{
	int	sp;
	int	i;

	i = 0;
	while (input[i])
	{
		if ((ft_strncmp(input + i, "&&", 2) == 0 || input[i] == '\\' ||
			ft_strncmp(input + i, "||", 2) == 0 || input[i] == '|')
			&& (i == 0 || input[i - 1] != '\\'))
		{
			if (!input[i + 1])
				return (FALSE);
			if (ft_strncmp(input + i, "&&", 2) == 0 ||
					ft_strncmp(input + i, "||", 2) == 0)
				sp = i + 2;
			else
				sp = i + 1;
			while (input[sp] && ft_isspace(input[sp]) == TRUE)
				sp++;
			if ((int)ft_strlen(input) == sp)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + c' feature, allocates/frees what needs to be freed.
**	-------------------------------------------------------------------------- +
*/

static int	input_exit_ctrl_c(char **input, char **ptr)
{
	ft_strdel(input);
	ft_strdel(ptr);
	return (!(*input = ft_strnew(0)) ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Display the accurate prompt, and ask the user to input characters.
**	When the typed character is a newline (`\n'), it checks the format of the
**	string (backslash, quotes) and ask the user to complete the input if needed.
**	-------------------------------------------------------------------------- +
*/

static int	input_catch_more(char **input, char ***heredocs)
{
	int	ret;

	if (hist_subs(input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (hist_append(&g_hist, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((ret = handle_heredocs(heredocs, *input)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ret == EXIT_CTRL_C)
	{
		ft_strdel(input);
		return (!(*input = ft_strnew(0)) ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int			input_catch(char **input, char ***heredocs)
{
	char	*str1;
	char	*str2;
	int		ret;

	hist_init(&g_hist);
	sh_prompt(PROMPT_BASIC);
	if (input_read(input, PROMPT_BASIC) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (input_check_quotes(*input) == FALSE ||
			input_check_operators(*input) == FALSE)
	{
		str1 = NULL;
		str2 = NULL;
		sh_prompt(PROMPT_QUOTE);
		if ((ret = input_read(&str1, PROMPT_QUOTE)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (ret == EXIT_CTRL_C)
			return (input_exit_ctrl_c(input, &str1));
		if (!(str2 = ft_strjoin_free(*input, "\n", 1)))
			return (EXIT_FAILURE);
		if (!(*input = ft_strjoin_free(str2, str1, 2)))
			return (EXIT_FAILURE);
	}
	return (input_catch_more(input, heredocs));
}
