/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:51:49 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:51:50 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	rotate_xy(int key, t_struct *fdf)
{
	if (key == 91 || key == 13)
	{
		fdf->step_angle_x -= 1.0;
		fdf->step_angle_x %= 360;
		fdf->angle_x = ((double)fdf->step_angle_x * M_PI) / 180.0;
	}
	if (key == 84 || key == 1)
	{
		fdf->step_angle_x += 1.0;
		fdf->step_angle_x %= 360;
		fdf->angle_x = ((double)fdf->step_angle_x * M_PI) / 180.0;
	}
	if (key == 86 || key == 0)
	{
		fdf->step_angle_y -= 1.0;
		fdf->step_angle_y %= 360;
		fdf->angle_y = ((double)fdf->step_angle_y * M_PI) / 180.0;
	}
	if (key == 88 || key == 2)
	{
		fdf->step_angle_y += 1.0;
		fdf->step_angle_y %= 360;
		fdf->angle_y = ((double)fdf->step_angle_y * M_PI) / 180.0;
	}
}

static void	rotation(int key, t_struct *fdf)
{
	if (key == 91 || key == 13 || key == 84 || key == 1 || key == 86 \
	|| key == 0 || key == 88 || key == 2)
		rotate_xy(key, fdf);
	else if (key == 89 || key == 12)
	{
		fdf->step_angle_z -= 1.0;
		fdf->step_angle_z %= 360;
		fdf->angle_z = ((double)fdf->step_angle_z * M_PI) / 180.0;
	}
	else if (key == 92 || key == 14)
	{
		fdf->step_angle_z += 1.0;
		fdf->step_angle_z %= 360;
		fdf->angle_z = ((double)fdf->step_angle_z * M_PI) / 180.0;
	}
	reprint(fdf);
}

static void	blanking(t_struct *fdf)
{
	if (!fdf->blank)
	{
		fdf->blank = 1;
		mlx_clear_window(fdf->mlx, fdf->win);
	}
	else
	{
		fdf->blank = 0;
		(fdf->tab == 1) ? p_menu(fdf) : reprint(fdf);
	}
}

static void	escaping(t_struct *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}

int			deal_key(int key, t_struct *fdf)
{
	if (key == 91 || key == 13 || key == 84 || key == 1 || key == 86 \
	|| key == 0 || key == 88 || key == 2 || key == 89 || key == 12 \
	|| key == 92 || key == 14)
		rotation(key, fdf);
	if (key == 11)
		blanking(fdf);
	if (key == 53)
		escaping(fdf);
	if (key == 48)
		tabulation(fdf);
	if (key == 36 || key == 69 || key == 49 || key == 78)
		zooming(key, fdf);
	if (key == 15)
		resetting(fdf);
	if (key >= 123 && key <= 126)
		moving(key, fdf);
	if (key == 34 || key == 31)
		scaling(key, fdf);
	return (0);
}
