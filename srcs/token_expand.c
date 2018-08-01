#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Does the expansion of environment $ENTRIES & status ("$?").
**	-------------------------------------------------------------------------- +
*/

static int	token_do_expand_tilde(char **line, char *var, char *left)
{
	char	*status;

	ft_strdel(&var);
	ft_strdel(&line[0]);
	if (!(status = ft_itoa(g_status)))
		return (EXIT_FAILURE);
	if (!(line[0] = ft_strjoin(status, left)))
		return (EXIT_FAILURE);
	ft_strdel(&status);
	ft_strdel(&left);
	return (EXIT_SUCCESS);
}

static int	token_do_expand(char **line, int vsize)
{
	extern char	**environ;
	char		*var;
	char		*left;
	int			i;

	left = NULL;
	vsize = 0;
	get_substring_size(line[0], &vsize);
	if (!(var = ft_strsub(line[0], 0, vsize)))
		return (EXIT_FAILURE);
	if (!(left = ft_strsub(line[0], vsize, ft_strlen(line[0]) - vsize)))
		return (EXIT_FAILURE);
	if (ft_strcmp(var, "$?") == 0)
		return (token_do_expand_tilde(line, var, left));
	i = -1;
	while (environ[++i])
		if (ft_strncmp(var + 1, environ[i], vsize - 1) == 0
				&& environ[i][vsize - 1] == '=')
			break ;
	ft_strdel(&line[0]);
	if (!(line[0] = ft_strjoin(environ[i] ? &(environ[i][vsize]) : "", left)))
		return (EXIT_FAILURE);
	ft_strdel(&var);
	ft_strdel(&left);
	return (environ[i] ? EXIT_SUCCESS : 2);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles environment $ENTRIES & status ("$?") expansion.
**	-------------------------------------------------------------------------- +
*/

static int	token_replace_dollarz(char **content, int ret)
{
	char	*str1;
	char	*str2;
	int		x;

	x = 0;
	while (content[0][x])
	{
		if (content[0][x] == '$' && content[0][x + 1]
			&& !ft_isspace(content[0][x + 1]) && content[0][x + 1] != '$')
		{
			if (!(str1 = ft_strsub(content[0], 0, x)))
				return (EXIT_FAILURE);
			if (!(str2 = ft_strsub(content[0], x, ft_strlen(content[0]) - x)))
				return (EXIT_FAILURE);
			if ((ret = token_do_expand(&str2, x)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			ft_strdel(&content[0]);
			if (!(content[0] = ft_strjoin_free(str1, str2, 2)))
				return (EXIT_FAILURE);
			ret != 2 ? get_substring_size(content[0], &x) : 0;
		}
		else
			x++;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles tilde (`~') expansion.
**	-------------------------------------------------------------------------- +
*/

static int	token_replace_tilde(t_token **head, t_token *node)
{
	char	*new_content;

	if (!env_get_val("HOME"))
	{
		token_del_node(head, node);
		return (sh_return("can't substitute, $HOME not set"));
	}
	if (!(new_content = ft_strjoin(env_get_val("HOME"), node->content + 1)))
		return (EXIT_FAILURE);
	ft_strdel(&node->content);
	node->content = new_content;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles following expansions:
**	- tilde (`~')
**	- environment $ENTRIES
**	- last command status ("$?")
**	-------------------------------------------------------------------------- +
*/

int			token_expand(t_token **head)
{
	t_token	*node;
	int		ret;

	ret = 0;
	node = *head;
	while (node)
	{
		if (node->type == TOKEN_WORD || node->type == TOKEN_DQUOTED)
		{
			if (ft_strcmp(node->content, "~") == 0 ||
					(node->content[0] == '~' && node->content[1] == '/'))
			{
				if (token_replace_tilde(head, node) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (ft_strchr(node->content, '$'))
			{
				if (token_replace_dollarz(&node->content, ret) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
