/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:55:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:55:05 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	tabulation(t_struct *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	if (fdf->tab == 0)
	{
		fdf->tab = 1;
		p_menu(fdf);
	}
	else
	{
		fdf->tab = 0;
		reprint(fdf);
	}
}

void	zooming(int key, t_struct *fdf)
{
	if (key == 36 || key == 69)
	{
		if ((fdf->z + fdf->step_z) * fdf->max_z * fdf->delta * \
		fdf->scale <= INT_MAX)
		{
			fdf->z += fdf->step_z;
			reprint(fdf);
		}
	}
	if (key == 49 || key == 78)
	{
		if ((fdf->z - fdf->step_z) * fdf->max_z * fdf->delta * \
		fdf->scale >= INT_MIN)
		{
			fdf->z -= fdf->step_z;
			reprint(fdf);
		}
	}
}

void	resetting(t_struct *fdf)
{
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	fdf->step_angle_x = 0;
	fdf->step_angle_y = 0;
	fdf->step_angle_z = 0;
	fdf->scale = 0.5;
	fdf->step_z = 0.1;
	fdf->step_move = 10;
	fdf->offset_x = fdf->reset_offset_x;
	fdf->offset_y = fdf->reset_offset_y;
	fdf->z = 1.0;
	fdf->tab = 0;
	fdf->blank = 0;
	fdf->delta = fdf->reset_delta;
	fdf->delta = fdf->reset_delta;
	reprint(fdf);
}

void	moving(int key, t_struct *fdf)
{
	if (key == 125 && (fdf->offset_y - fdf->step_move) >= INT_MIN)
	{
		fdf->offset_y -= fdf->step_move;
		reprint(fdf);
	}
	else if (key == 126 && (fdf->offset_y + fdf->step_move) <= INT_MAX)
	{
		fdf->offset_y += fdf->step_move;
		reprint(fdf);
	}
	if (key == 123 && (fdf->offset_x + fdf->step_move) < INT_MAX)
	{
		fdf->offset_x += fdf->step_move;
		reprint(fdf);
	}
	if (key == 124 && (fdf->offset_x - fdf->step_move) > INT_MIN)
	{
		fdf->offset_x -= fdf->step_move;
		reprint(fdf);
	}
}

void	mov(long long int *x, long long int *y, long long int *z, t_struct *fdf)
{
	fdf->x0 = (long long int)(((fdf->width - 1) * fdf->delta) / (2 / \
		fdf->scale));
	fdf->y0 = (long long int)(((fdf->height - 1) * fdf->delta) / (2 / \
		fdf->scale));
	fdf->tmp_x2 = *x;
	fdf->tmp_y2 = *y;
	fdf->tmp_z2 = *z;
	*y = (long long int)((fdf->tmp_y2 - fdf->y0) * cos(fdf->angle_x) + \
	(fdf->tmp_z2 + fdf->z0) * sin(fdf->angle_x) + fdf->y0);
	*z = (long long int)((fdf->tmp_z2 + fdf->z0) * cos(fdf->angle_x) - \
	(fdf->tmp_y2 - fdf->y0) * sin(fdf->angle_x) - fdf->z0);
	fdf->tmp_x2 = *x;
	fdf->tmp_y2 = *y;
	fdf->tmp_z2 = *z;
	*x = (long long int)((fdf->tmp_x2 - fdf->x0) * cos(fdf->angle_y) + \
	(fdf->tmp_z2 + fdf->z0) * sin(fdf->angle_y) + fdf->x0);
	*z = (long long int)((fdf->tmp_z2 + fdf->z0) * cos(fdf->angle_y) - \
	(fdf->tmp_x2 - fdf->x0) * sin(fdf->angle_y) - fdf->z0);
	fdf->tmp_x2 = *x;
	fdf->tmp_y2 = *y;
	fdf->tmp_z2 = *z;
	*x = (long long int)((fdf->tmp_x2 - fdf->x0) * cos(fdf->angle_z) - \
	(fdf->tmp_y2 - fdf->y0) * sin(fdf->angle_z) + fdf->x0);
	*y = (long long int)((fdf->tmp_y2 - fdf->y0) * cos(fdf->angle_z) + \
	(fdf->tmp_x2 - fdf->x0) * sin(fdf->angle_z) + fdf->y0);
}
