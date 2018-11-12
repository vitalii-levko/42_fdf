/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:44:08 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 22:45:36 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		res_fd(int *fd, char *str)
{
	close(*fd);
	*fd = open(str, O_RDONLY);
	if (*fd == -1)
		return (p_err(1, "Cannot access the map file"));
	return (0);
}

static size_t	get_height(int fd, char *str)
{
	size_t	h;

	h = 0;
	while (get_next_line(fd, &str) > 0)
	{
		h++;
		ft_strdel(&str);
		if (h > INT_MAX)
		{
			p_err(0, "Number of lines does not fit in the 'int' type");
			return (0);
		}
	}
	if (h == 0)
		return ((size_t)p_err(0, "No line in the map source file"));
	return (h);
}

int				init_fdf(t_struct *fdf, char *filepath)
{
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	fdf->step_angle_x = 0;
	fdf->step_angle_y = 0;
	fdf->step_angle_z = 0;
	fdf->scale = 0.5;
	fdf->max_z = 0;
	fdf->min_z = 0;
	fdf->z = 1.0;
	fdf->step_z = 0.1;
	fdf->step_move = 10;
	fdf->tab = 0;
	fdf->blank = 0;
	fdf->height = get_height(fdf->fd, NULL);
	if (fdf->height == 0)
		return (1);
	if (res_fd(&(fdf->fd), filepath))
		return (1);
	if (!(fdf->map = (long long int ***)ft_memalloc(sizeof(long long int **) \
		* (fdf->height + 1))))
		return (p_err(1, "Memory allocation failed"));
	fdf->map[fdf->height] = NULL;
	return (0);
}
