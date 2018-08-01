/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 11:41:28 by mgalliou          #+#    #+#             */
/*   Updated: 2017/06/28 10:53:45 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

int	ft_wcharlen(wint_t wint)
{
	if (wint <= 0x7F || (wint <= 0xFF && MB_CUR_MAX == 1))
		return (1);
	else if (wint <= 0x7FF && MB_CUR_MAX >= 2)
		return (2);
	else if (wint <= 0xFFFF && MB_CUR_MAX >= 3)
		return (3);
	else if (wint <= 0x10FFFF && MB_CUR_MAX >= 4)
		return (4);
	return (0);
}
