/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_hldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 22:24:04 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/27 23:34:39 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			hldi_left(int *count, int cwpm[4], long long int val, \
	t_plist *spec)
{
	if (spec->fg[4] && val >= 0)
		pc_di(count, '+', &(cwpm[1]));
	else if (spec->fg[3] && val >= 0)
		pc_di(count, ' ', &(cwpm[1]));
	if (val < 0)
	{
		pc_di(count, '-', &(cwpm[1]));
		val = -val;
	}
	while ((cwpm[2])-- > cwpm[0])
		pc_di(count, '0', &(cwpm[1]));
	ft_putnbr_ll(cwpm[3], val);
	*count += cwpm[0];
	cwpm[1] -= cwpm[0];
	while (cwpm[1] > 0)
		pc_di(count, ' ', &(cwpm[1]));
}

static void			hldi_r_prec(int *count, int wid, long long int *val, \
	t_plist *spec)
{
	while (wid > 0)
		pc_di(count, ' ', &wid);
	if (spec->fg[4] && *val >= 0)
		pc_di(count, '+', 0);
	else if (spec->fg[3] && *val >= 0)
		pc_di(count, ' ', 0);
	if (*val < 0)
	{
		pc_di(count, '-', 0);
		*val *= -1;
	}
}

static void			hldi_r_noprec(int *count, int wid, long long int *val, \
	t_plist *spec)
{
	if (spec->fg[1])
	{
		if (spec->fg[4] && *val >= 0)
			pc_di(count, '+', 0);
		else if (spec->fg[3] && *val >= 0)
			pc_di(count, ' ', 0);
		if (*val < 0)
		{
			pc_di(count, '-', 0);
			*val *= -1;
		}
		while (wid > 0)
			pc_di(count, '0', &wid);
		return ;
	}
	while (wid > 0)
		pc_di(count, ' ', &wid);
	if (spec->fg[4] && *val >= 0)
		pc_di(count, '+', 0);
	else
		(spec->fg[3] && *val >= 0) ? (pc_di(count, ' ', 0)) : (wid = 0);
	if (*val < 0)
		pc_di(count, '-', 0);
	if (*val < 0)
		*val *= -1;
}

static void			hldi_right(int *count, int cwpm[4], long long int val, \
	t_plist *spec)
{
	if (cwpm[2] > cwpm[0])
		cwpm[1] -= cwpm[2];
	else
		cwpm[1] -= cwpm[0];
	if (val < 0)
		cwpm[1] -= 1;
	else if (spec->fg[4])
		cwpm[1] -= 1;
	else if (spec->fg[3])
		cwpm[1] -= 1;
	if (spec->wp[2])
		hldi_r_prec(count, cwpm[1], &val, spec);
	else
		hldi_r_noprec(count, cwpm[1], &val, spec);
	while (cwpm[2] > cwpm[0])
		pc_di(count, '0', &(cwpm[2]));
	ft_putnbr_ll(cwpm[3], val);
	*count += cwpm[0];
}

void				cast_hldi(int *count, long long int val, t_plist *spec)
{
	long long int	nbr;
	int				cwpm[4];

	nbr = val;
	cwpm[0] = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwpm[1] = spec->wp[0];
	cwpm[2] = spec->wp[1];
	if (val == 0 && cwpm[2] == 0)
		return (ssmhldi_zero(count, cwpm[1], spec));
	cwpm[3] = 0;
	while (nbr /= 10)
		(cwpm[0])++;
	if (val == LONG_MIN)
	{
		cwpm[3] = 1;
		val++;
	}
	if (spec->fg[2])
		hldi_left(count, cwpm, val, spec);
	else
		hldi_right(count, cwpm, val, spec);
}
