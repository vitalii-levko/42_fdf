/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:38:00 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 22:56:54 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	save_str(t_struct *fdf, size_t h, size_t i, char **a)
{
	long long int	nb;

	while (a[i])
	{
		if (!(fdf->map[h][i] = (long long int *)ft_memalloc(\
			sizeof(long long int) * 2)))
			return (p_err(1, "Memory allocation failed"));
		if (ft_isnum(a[i]))
		{
			nb = ft_atoi(a[i]);
			if (nb > INT_MAX || nb < INT_MIN)
				return (p_err(1, "Coordinates does not fit in the 'int' type"));
			save_z(fdf, nb);
			fdf->map[h][i][0] = (int)nb;
			fdf->map[h][i][1] = ft_atoh("ffffff", 16);
		}
		else
		{
			if (save_color(fdf, a[i], i, h))
				return (1);
		}
		i++;
	}
	return ((i == 0) ? 1 : 0);
}

static int	init_offset(t_struct *fdf, char **str)
{
	fdf->x2 = 0;
	fdf->y2 = 0;
	fdf->z1 = 0;
	fdf->z2 = 0;
	mov(&fdf->x, &fdf->y2, &fdf->z1, fdf);
	mov(&fdf->x2, &fdf->y, &fdf->z2, fdf);
	if (fdf->x > INT_MAX || fdf->y > INT_MAX || fdf->x2 > INT_MAX || fdf->y2 > \
	INT_MAX || fdf->z1 > INT_MAX || fdf->z2 > INT_MAX)
	{
		ret_a(NULL, p_err(1, "Calculation of coordinates is out of 'int' "
				"range"), str);
		return (1);
	}
	fdf->offset_x = llabs(fdf->x2) + (fdf->init_width - llabs(fdf->x) - \
	llabs(fdf->x2)) / 2;
	fdf->offset_y = (fdf->init_height - llabs(fdf->y2) - llabs(fdf->y)) / 2;
	if (fdf->offset_x > INT_MAX || fdf->offset_y > INT_MAX)
	{
		ret_a(NULL, p_err(1, "Calculation of coordinates is out of 'int' "
				"range"), str);
		return (1);
	}
	fdf->reset_offset_x = fdf->offset_x;
	fdf->reset_offset_y = fdf->offset_y;
	return (0);
}

static int	init_map(t_struct *fdf, char **str, size_t *w, char ***a)
{
	*a = get_width(*str, w);
	if (!*a || *w == 0)
		return (ret_a(a, 1, str));
	fdf->width = *w;
	fdf->delta = (int)((double)((fdf->init_height > fdf->init_width) ? \
	fdf->init_width : fdf->init_height) / (double)(((fdf->init_height > \
	fdf->init_width) ? fdf->width : fdf->height) + 1));
	fdf->reset_delta = fdf->delta;
	fdf->delta = fdf->delta;
	fdf->reset_delta = fdf->delta;
	fdf->step_y = fdf->delta;
	fdf->x = (long long int)((fdf->width - 1) * fdf->delta);
	fdf->x *= fdf->scale;
	fdf->y = (long long int)((fdf->height - 1) * fdf->delta);
	fdf->y *= fdf->scale;
	if (fdf->x > INT_MAX || fdf->y > INT_MAX)
	{
		ret_a(NULL, p_err(1, "Calculation of coordinates is out of 'int' "
				"range"), str);
		return (1);
	}
	fdf->z0 = 0;
	return (init_offset(fdf, str));
}

static int	check_line(t_struct *fdf, char **str, size_t *w, char ***a)
{
	if (*w == 0)
	{
		if (init_map(fdf, str, w, a))
			return (1);
	}
	else
	{
		*a = get_width(*str, w);
		if (!*a)
			return (ret_a(a, 1, str));
		if (fdf->width != *w)
			return (p_err(ret_a(a, 1, str), "Line length mismatch"));
	}
	return (0);
}

int			save_map(t_struct *fdf, char *str, size_t h, size_t w)
{
	char	**a;

	a = NULL;
	while (get_next_line(fdf->fd, &str) > 0)
	{
		if (check_line(fdf, &str, &w, &a))
			return (1);
		if (!(fdf->map[h] = (long long int **)ft_memalloc(\
			sizeof(long long int *) * (w + 1))))
			return (p_err(ret_a(&a, 1, &str), "Memory allocation failed"));
		fdf->map[h][w] = NULL;
		if (save_str(fdf, h, 0, a))
			return (ret_a(&a, 1, &str));
		if (h != 0)
		{
			if (print_line(fdf, h - 1, 0))
				return (ret_a(&a, 1, &str));
		}
		ret_a(&a, 0, &str);
		h++;
	}
	if (w == 0 || print_line(fdf, h - 1, 0))
		return (1);
	p_info(fdf, NULL, NULL, NULL);
	return (0);
}
