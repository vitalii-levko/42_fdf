/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:17:46 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 14:17:47 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_arrdel(char ***arr)
{
	char	**curr;
	char	*str;

	if (arr && *arr)
	{
		curr = *arr;
		while (*curr)
		{
			str = *curr;
			curr++;
			ft_strdel(&str);
		}
		free(*arr);
		*arr = NULL;
		arr = NULL;
	}
}
