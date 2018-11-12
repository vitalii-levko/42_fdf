/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:21:45 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:21:46 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ret_a(char ***arr, int ret, char **str)
{
	if (str)
		ft_strdel(str);
	if (arr)
		ft_arrdel(arr);
	return (ret);
}

int		ret_f(t_struct *fdf, int ret, long long int ***curr)
{
	int		i;
	int		j;

	if (fdf)
	{
		if (fdf->map)
		{
			i = 0;
			curr = fdf->map;
			while (curr[i])
			{
				j = 0;
				while (curr[i][j])
				{
					free(curr[i][j]);
					j++;
				}
				free(curr[i]);
				i++;
			}
			free(fdf->map);
		}
		free(fdf);
	}
	return (ret);
}

int		ret_fd(t_struct *fdf, int ret)
{
	close(fdf->fd);
	return (ret_f(fdf, ret, NULL));
}
