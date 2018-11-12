/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:34:56 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 23:09:45 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			check_max(t_struct *fdf, int cs)
{
	if (cs == 1)
	{
		if (fdf->x2 > INT_MAX || fdf->y2 > INT_MAX || fdf->z2 > INT_MAX ||
			fdf->x2 < INT_MIN || fdf->y2 < INT_MIN || fdf->z2 < INT_MIN)
			return (1);
	}
	else if (cs == 0)
	{
		if (fdf->x > INT_MAX || fdf->y > INT_MAX || fdf->x2 > INT_MAX ||
			fdf->y2 > INT_MAX || fdf->z1 > INT_MAX || fdf->z2 > INT_MAX ||
			fdf->x < INT_MIN || fdf->y < INT_MIN || fdf->x2 < INT_MIN ||
			fdf->y2 < INT_MIN || fdf->z1 < INT_MIN || fdf->z2 < INT_MIN)
			return (1);
	}
	else
	{
		if (fdf->x > INT_MAX || fdf->y > INT_MAX || fdf->z1 > INT_MAX ||
			fdf->x < INT_MIN || fdf->y < INT_MIN || fdf->z1 < INT_MIN)
			return (1);
	}
	return (0);
}

static int	init_start_line(t_struct *fdf, size_t i, size_t j)
{
	fdf->c1 = fdf->map[i][j][1];
	fdf->z1 = fdf->map[i][j][0];
	fdf->z1 *= fdf->delta;
	fdf->z1 = (long long int)((double)fdf->z1 * fdf->z);
	fdf->z1 *= fdf->scale;
	fdf->x = fdf->step_x - fdf->delta;
	fdf->x *= fdf->scale;
	fdf->y = fdf->step_y - fdf->delta;
	fdf->y *= fdf->scale;
	if (check_max(fdf, 2))
		return (p_err(1, "Calculation of coordinates is out of 'int' range"));
	fdf->tmp_x = fdf->x;
	fdf->tmp_y = fdf->y;
	fdf->tmp_z = fdf->z1;
	return (0);
}

static int	init_horiz_line(t_struct *fdf, size_t i, size_t j)
{
	fdf->c2 = fdf->map[i][j + 1][1];
	fdf->z2 = fdf->map[i][j + 1][0] * fdf->delta;
	fdf->z2 = (long long int)((double)fdf->z2 * fdf->z);
	fdf->z2 *= fdf->scale;
	fdf->x2 = (long long int)(fdf->step_x * fdf->scale);
	fdf->y2 = (long long int)((fdf->step_y - fdf->delta) * fdf->scale);
	if (check_max(fdf, 1))
		return (p_err(1, "Calculation of coordinates is out of 'int' range"));
	fdf->z0 = (0 + fdf->tmp_z) / 2;
	mov(&fdf->x, &fdf->y, &fdf->z1, fdf);
	fdf->z0 = (fdf->z2 + 0) / 2;
	mov(&fdf->x2, &fdf->y2, &fdf->z2, fdf);
	if (check_max(fdf, 0))
		return (p_err(1, "Calculation of coordinates is out of 'int' range"));
	fdf->x += fdf->offset_x;
	fdf->y += fdf->offset_y;
	fdf->x2 += fdf->offset_x;
	fdf->y2 += fdf->offset_y;
	fdf->draw_dx = llabs(fdf->x2 - fdf->x);
	fdf->draw_dy = llabs(fdf->y2 - fdf->y);
	fdf->error = fdf->draw_dx - fdf->draw_dy;
	draw(fdf, 0, 0, 0);
	return (0);
}

static int	init_vertic_line(t_struct *fdf, size_t i, size_t j)
{
	fdf->c2 = fdf->map[i + 1][j][1];
	fdf->z2 = (long long int)(fdf->map[i + 1][j][0] * fdf->delta * fdf->z \
		* fdf->scale);
	fdf->x2 = (long long int)((fdf->step_x - fdf->delta) * fdf->scale);
	fdf->y2 = (long long int)(fdf->step_y * fdf->scale);
	if (check_max(fdf, 1))
		return (p_err(1, "Calculation of coordinates is out of 'int' range"));
	fdf->z0 = (0 + fdf->tmp_z) / 2;
	fdf->z1 = fdf->tmp_z;
	fdf->x = fdf->tmp_x;
	fdf->y = fdf->tmp_y;
	mov(&fdf->x, &fdf->y, &fdf->z1, fdf);
	fdf->z0 = (fdf->z2 + 0) / 2;
	mov(&fdf->x2, &fdf->y2, &fdf->z2, fdf);
	if (check_max(fdf, 0))
		return (p_err(1, "Calculation of coordinates is out of 'int' range"));
	fdf->x += fdf->offset_x;
	fdf->y += fdf->offset_y;
	fdf->x2 += fdf->offset_x;
	fdf->y2 += fdf->offset_y;
	fdf->draw_dx = llabs(fdf->x2 - fdf->x);
	fdf->draw_dy = llabs(fdf->y2 - fdf->y);
	fdf->error = fdf->draw_dx - fdf->draw_dy;
	draw(fdf, 0, 0, 0);
	return (0);
}

int			print_line(t_struct *fdf, size_t i, size_t j)
{
	fdf->step_x = fdf->delta;
	while (fdf->map[i][j])
	{
		if (init_start_line(fdf, i, j))
			return (1);
		if (i == 0 && j == 0 && !fdf->map[i][j + 1] && !fdf->map[i + 1])
		{
			if (draw_point(fdf, i, j))
				return (1);
		}
		if (fdf->map[i][j + 1])
		{
			if (init_horiz_line(fdf, i, j))
				return (1);
		}
		if (fdf->map[i + 1])
		{
			if (init_vertic_line(fdf, i, j))
				return (1);
		}
		fdf->step_x += fdf->delta;
		j++;
	}
	fdf->step_y += fdf->delta;
	return (0);
}
