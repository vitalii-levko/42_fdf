/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:21:24 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 14:21:25 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_isnum(char *str)
{
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if (!*str)
			return (0);
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}
