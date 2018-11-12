/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_mu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 23:49:38 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 12:09:40 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		ft_putnbr_mu(uintmax_t nbr)
{
	uintmax_t	tmp;
	uintmax_t	cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar((nbr / cnt) + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	ft_putchar(nbr + '0');
}

void			mslu_zero(int *count, int wid)
{
	while (wid > 0)
		pc_di(count, ' ', &wid);
}

void			mslu_left(int *count, int cwp[3])
{
	*count += cwp[0];
	cwp[1] -= cwp[0];
	while (cwp[1] > 0)
		pc_di(count, ' ', &(cwp[1]));
}

void			mslu_rt(int *count, int cwp[3], t_plist *spec)
{
	cwp[1] -= (cwp[2] > cwp[0]) ? cwp[2] : cwp[0];
	if (spec->wp[2])
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
	else
		while (cwp[1] > 0)
			pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
	while (cwp[2] > cwp[0])
		pc_di(count, '0', &(cwp[2]));
}

void			cast_mu(int *count, uintmax_t val, t_plist *spec)
{
	uintmax_t	nbr;
	int			cwp[3];

	nbr = val;
	cwp[0] = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	if (val == 0 && cwp[2] == 0)
		return (mslu_zero(count, cwp[1]));
	while (nbr /= 10)
		(cwp[0])++;
	if (spec->fg[2])
	{
		while ((cwp[2])-- > cwp[0])
			pc_di(count, '0', &(cwp[1]));
		ft_putnbr_mu(val);
		mslu_left(count, cwp);
		return ;
	}
	mslu_rt(count, cwp, spec);
	ft_putnbr_mu(val);
	*count += cwp[0];
}
