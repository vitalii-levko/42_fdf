/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:53:03 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:53:05 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	precalc_offset(t_struct *fdf)
{
	fdf->offset_x = fdf->reset_offset_x;
	fdf->offset_y = fdf->reset_offset_y;
	fdf->x2 = 0;
	fdf->y2 = 0;
	fdf->z1 = fdf->min_z;
	fdf->z2 = fdf->max_z;
	fdf->x = (long long int)((fdf->width - 1) * fdf->delta);
	fdf->x *= fdf->scale;
	fdf->y = (long long int)((fdf->height - 1) * fdf->delta);
	fdf->y *= fdf->scale;
}

static void	setup_offset(t_struct *fdf)
{
	if (fdf->x2 < 0)
		fdf->offset_x = llabs(fdf->x2) + (fdf->init_width - llabs(fdf->x) - \
		llabs(fdf->x2)) / 2;
	else if (fdf->x < 0)
		fdf->offset_x = llabs(fdf->x) + (fdf->init_width - llabs(fdf->x) - \
		llabs(fdf->x2)) / 2;
	else
		fdf->offset_x = (fdf->init_width - llabs(fdf->x) - llabs(fdf->x2)) / 2;
	if (fdf->y2 < 0)
		fdf->offset_y = llabs(fdf->y2) + (fdf->init_height - llabs(fdf->y2) - \
		llabs(fdf->y)) / 2;
	else if (fdf->y < 0)
		fdf->offset_y = llabs(fdf->y) + (fdf->init_height - llabs(fdf->y2) - \
		llabs(fdf->y)) / 2;
	else
		fdf->offset_y = (fdf->init_height - llabs(fdf->y2) - llabs(fdf->y)) / 2;
}

static void	calc_offset(t_struct *fdf)
{
	if (fdf->x > INT_MAX || fdf->y > INT_MAX
		|| fdf->x < INT_MIN || fdf->y < INT_MIN)
		exit(p_err(1, "Calculation of coordinates is out of 'int' range"));
	fdf->z0 = 0;
	mov(&fdf->x, &fdf->y2, &fdf->z1, fdf);
	mov(&fdf->x2, &fdf->y, &fdf->z2, fdf);
	if (fdf->x > INT_MAX || fdf->y > INT_MAX || fdf->x2 > INT_MAX || fdf->y2 > \
	INT_MAX || fdf->z1 > INT_MAX || fdf->z2 > INT_MAX)
		exit(p_err(1, "Calculation of coordinates is out of 'int' range"));
	setup_offset(fdf);
	if (fdf->offset_x > INT_MAX || fdf->offset_y > INT_MAX)
		exit(p_err(1, "Calculation of coordinates is out of 'int' range"));
}

void		scaling(int key, t_struct *fdf)
{
	if (key == 34 && fdf->scale < 32)
	{
		fdf->step_move *= 2;
		fdf->scale *= 2;
		precalc_offset(fdf);
		calc_offset(fdf);
		reprint(fdf);
	}
	if (key == 31 && fdf->scale > 0.12)
	{
		fdf->step_move /= 2;
		fdf->scale /= 2;
		precalc_offset(fdf);
		calc_offset(fdf);
		reprint(fdf);
	}
}
