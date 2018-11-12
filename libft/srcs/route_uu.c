/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_uU.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 23:40:21 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 12:10:16 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_putnbr_su(size_t nbr)
{
	size_t					tmp;
	size_t					cnt;

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

static void	cast_su(int *count, size_t val, t_plist *spec)
{
	size_t					nbr;
	int						cwp[3];

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
		while (cwp[2]-- > cwp[0])
			pc_di(count, '0', &(cwp[1]));
		ft_putnbr_su(val);
		mslu_left(count, cwp);
		return ;
	}
	mslu_rt(count, cwp, spec);
	ft_putnbr_su(val);
	*count += cwp[0];
}

static void	ft_putnbr_lu(unsigned long long int nbr)
{
	unsigned long long int	tmp;
	unsigned long long int	cnt;

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

static void	cast_lu(int *count, unsigned long long int val, \
	t_plist *spec)
{
	unsigned long long int	nbr;
	int						cwp[3];

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
		ft_putnbr_lu(val);
		mslu_left(count, cwp);
		return ;
	}
	mslu_rt(count, cwp, spec);
	ft_putnbr_lu(val);
	*count += cwp[0];
}

void		route_uu(int *count, char f, va_list *ap, t_plist *spec)
{
	if (spec->jz[1] && f != 'U')
		cast_su(count, (size_t)(va_arg(*ap, size_t)), spec);
	else if (spec->jz[0] && f != 'U')
		cast_mu(count, (uintmax_t)(va_arg(*ap, uintmax_t)), spec);
	else if (spec->ll[1] && f != 'U')
		cast_lu(count, (unsigned long long int)(va_arg(*ap, \
			unsigned long long int)), spec);
	else if (spec->ll[0])
		cast_lu(count, (unsigned long int)(va_arg(*ap, unsigned long int)), \
			spec);
	else if (spec->hh[1] && f != 'U')
		cast_lu(count, (unsigned char)(va_arg(*ap, unsigned int)), spec);
	else if (spec->hh[0] && f != 'U')
		cast_lu(count, (unsigned short int)(va_arg(*ap, unsigned int)), spec);
	else if (f != 'U')
		cast_lu(count, (unsigned int)(va_arg(*ap, unsigned int)), spec);
}
