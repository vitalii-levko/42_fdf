/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 11:49:12 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 12:10:01 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				ft_putnbr_m(int minval, intmax_t nbr)
{
	intmax_t		tmp;
	intmax_t		cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar(nbr / cnt + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	if (minval)
		nbr++;
	ft_putchar(nbr + '0');
}

void				ft_putnbr_ss(int minval, ssize_t nbr)
{
	ssize_t			tmp;
	ssize_t			cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar(nbr / cnt + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	if (minval)
		nbr++;
	ft_putchar(nbr + '0');
}

void				ft_putnbr_ll(int minval, long long int nbr)
{
	long long int	tmp;
	long long int	cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar(nbr / cnt + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	if (minval)
		nbr++;
	ft_putchar(nbr + '0');
}

void				ssmhldi_zero(int *count, int wid, t_plist *spec)
{
	while (wid > 0)
	{
		if (spec->fg[4] && wid == 1)
			ft_putchar('+');
		else
			ft_putchar(' ');
		wid--;
		(*count)++;
	}
}

void				route_di(int *count, char f, va_list *ap, t_plist *spec)
{
	if (spec->jz[1] == 1 && f != 'D')
		cast_ssdi(count, (ssize_t)(va_arg(*ap, ssize_t)), spec);
	else if (spec->jz[0] == 1 && f != 'D')
		cast_mdi(count, (intmax_t)(va_arg(*ap, intmax_t)), spec);
	else if (spec->ll[1] && f != 'D')
		cast_hldi(count, (long long int)(va_arg(*ap, long long int)), spec);
	else if (spec->ll[0])
		cast_hldi(count, (long int)(va_arg(*ap, long int)), spec);
	else if (spec->hh[1] && f != 'D')
		cast_hldi(count, (signed char)(va_arg(*ap, int)), spec);
	else if (spec->hh[0] && f != 'D')
		cast_hldi(count, (short int)(va_arg(*ap, int)), spec);
	else if (f != 'D')
		cast_hldi(count, (int)(va_arg(*ap, int)), spec);
}
