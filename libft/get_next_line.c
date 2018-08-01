#include "libft.h"

/*
**	fd_to_string() reads on a given file descriptor, and returns a new string
**	containing the readen data from the file descriptor, or NULL on failure.
*/

static char		*fd_to_string(const int fd, char *mem)
{
	char	*buffer;
	char	*tmp;
	int		ret;

	if (!(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (NULL);
	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		if (ret == -1)
		{
			ft_strdel(&buffer);
			return (NULL);
		}
		*(buffer + ret) = '\0';
		if (!(tmp = ft_strjoin(mem, buffer)))
			return (NULL);
		ft_strdel(&mem);
		mem = tmp;
		if ((ft_strchr(mem, '\n')))
			break ;
	}
	ft_strdel(&buffer);
	return (mem);
}

/*
**	change_values() cuts the returned string (or previous `mem` value if it
**	still contains '\n' character) to the very first '\n' character, copies it
**	into `line`, and copies the remaining characters into `mem`.
*/

static int		change_values(char **line, char **mem, char **str)
{
	if (!(*str = ft_strdup(*mem)))
		return (-1);
	ft_strdel(mem);
	if (**str == '\n')
	{
		if (!(*mem = ft_strdup(*str + 1)))
			return (-1);
		ft_strdel(str);
		if (!(*line = ft_strnew(0)))
			return (-1);
		return (1);
	}
	if (!(*mem = ft_strchr(*str, '\n') ?
			ft_strdup(ft_strchr(*str, '\n') + 1) :
			ft_strnew(0)))
		return (-1);
	if ((ft_strchr(*str, '\n')))
		*ft_strchr(*str, '\n') = '\0';
	*line = *str;
	return (0);
}

/*
**	fd_select() helps managing multiple file descriptor, by returning
**	the memory string corresponding to the file descriptor.
*/

static t_mfd	*fd_select(const int fd, t_mfd **head)
{
	t_mfd	*elm;

	elm = *head;
	while (elm)
	{
		if (elm->fd == (int)fd)
			return (elm);
		elm = elm->next;
	}
	if (!elm)
	{
		if (!(elm = malloc(sizeof(t_mfd))))
			return (NULL);
		if (!(elm->mem = ft_strnew(0)))
			return (NULL);
		elm->fd = (int)fd;
		elm->next = *head;
		*head = elm;
	}
	return (elm);
}

/*
**	get_next_line() returns a line ending with a newline,
**	read from a file descriptor.
**	-	return (1) if a line has been read,
**	-	return (0) when reading has been completed,
**	-	return (-1) if an error occurred.
*/

int				get_next_line(const int fd, char **line)
{
	static t_mfd	*head = NULL;
	t_mfd			*curr;
	char			*str;
	int				ret;

	if (!line || fd < 0)
		return (-1);
	if (!(curr = fd_select(fd, &head)))
		return (-1);
	if (!(ft_strchr(curr->mem, '\n')))
		if (!(curr->mem = fd_to_string(fd, curr->mem)))
			return (-1);
	ret = change_values(line, &curr->mem, &str);
	return (ret == 0 ? !!(*(str + 0)) : ret);
}
