/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:59:21 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 23:09:22 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	apply_opacity(int c1, int c2, double opacity, int applied)
{
	if (c1 == c2)
		return (c1);
	applied = (int)((double)c1 + (double)(c2 - c1) * opacity);
	return (applied);
}

static int	new_col(int c1, int c2, double opacity, int new)
{
	int		red;
	int		green;
	int		blue;

	if (c1 == c2)
		return (c1);
	red = apply_opacity((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, opacity, 0);
	green = apply_opacity((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, opacity, 0);
	blue = apply_opacity(c1 & 0xFF, c2 & 0xFF, opacity, 0);
	new = red << 16 | green << 8 | blue;
	return (new);
}

void		draw(t_struct *fdf, int new_c, double count_steps, double step_x)
{
	fdf->sign_x = fdf->x < fdf->x2 ? 1 : -1;
	fdf->sign_y = fdf->y < fdf->y2 ? 1 : -1;
	count_steps = sqrt(pow((fdf->x2 - fdf->x), 2) + pow((fdf->y2 - fdf->y), 2));
	step_x = (count_steps != 0) ? (1.0 / count_steps) : 0;
	fdf->opacity = (step_x < 1) ? step_x : 0;
	new_c = new_col(fdf->c1, fdf->c2, fdf->opacity, 0);
	mlx_pixel_put(fdf->mlx, fdf->win, (int)fdf->x2, (int)fdf->y2, fdf->c2);
	while (fdf->x != fdf->x2 || fdf->y != fdf->y2)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, (int)fdf->x, (int)fdf->y, new_c);
		fdf->error2 = fdf->error * 2;
		if (fdf->error2 > -fdf->draw_dy)
		{
			fdf->error -= fdf->draw_dy;
			fdf->x += fdf->sign_x;
		}
		else
		{
			fdf->error += fdf->draw_dx;
			fdf->y += fdf->sign_y;
		}
		if (fdf->opacity + step_x < 1)
			fdf->opacity += step_x;
		new_c = new_col(fdf->c1, fdf->c2, fdf->opacity, 0);
	}
}

int			draw_point(t_struct *fdf, size_t i, size_t j)
{
	fdf->c2 = fdf->map[i][j][1];
	fdf->z2 = fdf->map[i][j][0] * fdf->delta;
	fdf->z2 = (long long int)((double)fdf->z2 * fdf->z);
	fdf->z2 *= fdf->scale;
	fdf->x2 = (long long int)((fdf->step_x - fdf->delta) * fdf->scale);
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
