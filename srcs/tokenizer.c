#include "../incs//minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Goes through the function array as long as the called function returns 0.
**	When a function returns 1, it means its execution has succeeded.
**	-------------------------------------------------------------------------- +
*/

static int	tokenizer_functions(t_token **head, t_tokenizer *data, char ch)
{
	static int	(*token_fct[])(t_token **, t_tokenizer *, char) = {
	token_process_1,
	token_process_2,
	token_process_3,
	token_process_4,
	token_process_5,
	token_process_6,
	token_process_7,
	token_process_8,
	token_process_9,
	token_process_10,
	NULL};
	int			ret;
	int			i;

	i = 0;
	while (token_fct[i] && (ret = token_fct[i](head, data, ch)) == 0)
		i++;
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Initializes `tokenizer` structure, then call token functions on each
**	character of the input, char after char.
**	-------------------------------------------------------------------------- +
*/

static void	tokenizer_init(t_token **head, t_tokenizer *data)
{
	*head = NULL;
	data->token = NULL;
	data->sq = FALSE;
	data->dq = FALSE;
	data->bs = FALSE;
	data->op = FALSE;
}

int			tokenizer(char *input, t_token **tlist)
{
	t_tokenizer	data;
	t_token		*head;
	char		ch;
	int			ret;
	int			i;

	i = 0;
	tokenizer_init(&head, &data);
	while (i <= (int)ft_strlen(input))
	{
		ch = *(input + i++);
		if ((ret = tokenizer_functions(&head, &data, ch)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 2)
			break ;
	}
	if (token_add(&head, "EOL", TOKEN_EOL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (token_rework(&head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*tlist = head;
	ft_strdel(&data.token);
	return (EXIT_SUCCESS);
}
