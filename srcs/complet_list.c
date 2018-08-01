#include "../incs/minishell.h"

struct s_list_words		*add_list_word(void)
{
	t_list_words		*new;

	if (!(new = ft_memalloc(sizeof(t_list_words))))
		return (NULL);
	return (new);
}

int						is_matching(char *file, char *last)
{
	int		n;

	n = ft_strlen(last);
	if ((file[0] == '.' && file[1] == '\0') ||
		(file[0] == '.' && file[1] == '.' && file[2] == '\0'))
		return (0);
	if (!last || !last[0])
		return (1);
	if (ft_strncmp(file, last, n) == 0)
		return (1);
	return (0);
}

int						fill_infos(t_complet *comp, struct dirent *infos)
{
	int	n;

	n = ft_strlen(infos->d_name);
	if (!(comp->list->name = ft_strdup(infos->d_name)))
		return (0);
	if (comp->len_max < n)
		comp->len_max = n;
	comp->nb_words++;
	return (1);
}

int						get_list(t_complet *comp, DIR *dir, t_list_words **tmp)
{
	struct dirent	*infos;

	while ((infos = readdir(dir)))
	{
		if (is_matching(infos->d_name, comp->last))
		{
			if (*tmp != NULL)
			{
				comp->list->next = add_list_word();
				comp->list = comp->list->next;
			}
			else
			{
				comp->list = add_list_word();
				*tmp = comp->list;
			}
			if (fill_infos(comp, infos) == 0)
				return (0);
		}
	}
	return (1);
}
