/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:08:56 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 22:58:18 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static size_t	arr_len(char **arr)
{
	size_t	l;

	l = 0;
	while (arr[l])
	{
		l++;
		if (l > INT_MAX)
		{
			p_err(0, "Number of coordinates per line does not fit int the 'int'"
					" type");
			return (0);
		}
	}
	if (l == 0)
		return ((size_t)p_err(0, "No coordinate per line was found"));
	return (l);
}

static int		is_color(char *str)
{
	size_t	len;

	if (str)
	{
		len = ft_strlen(str);
		if (10 < len || len < 3)
			return (0);
		if (str[0] != '0' && str[1] != 'x')
			return (0);
		str += 2;
		while (*str)
		{
			if (!(('0' <= *str && *str <= '9') || ('A' <= *str && *str <= 'F') \
			|| ('a' <= *str && *str <= 'f')))
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

char			**get_width(char *str, size_t *w)
{
	char	**arr;

	arr = ft_strsplit(str, ' ');
	if (!arr)
	{
		p_err(0, "Empty line in the map source file");
		return (NULL);
	}
	*w = arr_len(arr);
	return (arr);
}

void			save_z(t_struct *fdf, long long int nb)
{
	if (fdf->max_z < nb)
		fdf->max_z = nb;
	else if (fdf->min_z > nb)
		fdf->min_z = nb;
}

int				save_color(t_struct *fdf, char *str, size_t i, size_t h)
{
	char			**a;
	long long int	nb;

	a = ft_strsplit(str, ',');
	if (!a)
		return (p_err(ret_a(&a, 1, NULL), "Invalid coordinate"));
	if (!ft_isnum(a[0]))
	{
		p_err(ret_a(&a, 1, NULL), "Coordinate is not a number of the 'int' "
			"type");
		return (1);
	}
	nb = ft_atoi(a[0]);
	if (nb > INT_MAX || nb < INT_MIN)
	{
		p_err(ret_a(&a, 1, NULL), "Coordinates does not fit in the 'int' type");
		return (1);
	}
	save_z(fdf, nb);
	fdf->map[h][i][0] = (int)nb;
	if (!is_color(a[1]))
		return (p_err(ret_a(&a, 1, NULL), "Invalid color"));
	fdf->map[h][i][1] = ft_atoh(a[1] + 2, 16);
	return (ret_a(&a, 0, NULL));
}
