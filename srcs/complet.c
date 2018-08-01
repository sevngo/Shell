#include "../incs/minishell.h"

int		free_complet(t_complet *comp)
{
	t_list_words	*tmp;

	ft_free(comp->word);
	ft_free(comp->path);
	ft_free(comp->last);
	while (comp->list)
	{
		tmp = comp->list;
		comp->list = comp->list->next;
		ft_free(tmp->name);
		ft_free(tmp);
	}
	return (1);
}

char	*get_last_word(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
		i++;
	while (!ft_isspace(input[i]) && i > 0)
		i--;
	if (ft_isspace(input[i]))
		i++;
	return (ft_strdup(&(input[i])));
}

int		get_last_path(t_complet *comp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (comp->last[i] == '\0')
		return (0);
	while (comp->last[i])
		i++;
	while ((comp->last[i] != '/' || comp->last[i] == '\0') && i > 0)
		i--;
	if (i != 0)
		if (!(comp->path = ft_strndup(comp->last, i + 1)))
			return (0);
	if (i == 0)
		if (!(comp->path = (comp->last[0] == '/') ?
												ft_strdup("/") : ft_strdup("")))
			return (0);
	if (comp->last[i] == '/')
		i++;
	if (!(tmp = ft_strdup(&(comp->last[i]))))
		return (0);
	ft_free(comp->last);
	comp->last = tmp;
	return (1);
}

char	*completion(char *input)
{
	int			x;
	t_complet	comp;

	ft_bzero(&comp, sizeof(t_complet));
	if (!(comp.last = get_last_word(input)))
		return (input);
	x = complet_wich_case(input, comp.last);
	if (x == 0)
		return (input);
	get_last_path(&comp);
	if (x == CASE_PATH)
		case_path(&comp);
	else if (x == CASE_PWD)
		case_pwd(&comp);
	else if (x == CASE_ABSOLUTE)
		case_absolute(&comp);
	if (!(comp.word == NULL && comp.list == NULL))
	{
		input = print_words(&comp, input);
	}
	free_complet(&comp);
	return (input);
}
