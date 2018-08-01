/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 11:08:02 by mgalliou          #+#    #+#             */
/*   Updated: 2017/06/23 15:56:43 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wstrtoa(wchar_t *wstr)
{
	char	*new;
	char	*tmp;

	new = ft_strnew(ft_wstrlen(wstr));
	while (*wstr)
	{
		if (!(tmp = ft_wchartoa(*wstr++)))
		{
			ft_strdel(&new);
			return (NULL);
		}
		new = ft_strcat(new, tmp);
		ft_strdel(&tmp);
	}
	return (new);
}
