/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_oo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 23:18:10 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:55:10 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static uintmax_t	ft_pow_mu(int nbr, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (uintmax_t)(nbr * ft_pow_mu(nbr, pow - 1));
}

char				*ft_itoa_base_mu(char c, uintmax_t val, int base)
{
	int				i;
	char			*str;

	i = 1;
	str = NULL;
	while (ft_pow_mu(base, i) - 1 < val)
		i++;
	str = ft_strnew(i);
	if (val == 0)
		return (str);
	while (i-- > 0)
	{
		str[i] = (val % base) + (val % base > 9 ? c - 10 : '0');
		val /= base;
	}
	return (str);
}

static void			o_right(int *count, int cwp[3], t_plist *spec)
{
	if (spec->fg[0] && cwp[2] <= cwp[0])
		(cwp[1])--;
	else if (cwp[2] > cwp[0])
		cwp[1] -= cwp[2];
	if (cwp[2] <= cwp[0])
		cwp[1] -= cwp[0];
	if (spec->wp[2])
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
	else
		while (cwp[1] > 0)
			pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
	if (spec->fg[0])
		pc_di(count, '0', &(cwp[2]));
	while (cwp[2] > cwp[0])
		pc_di(count, '0', &(cwp[2]));
}

static void			cast_o(int *count, char *val, t_plist *spec)
{
	int				cwp[3];

	cwp[0] = 0;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	cwp[0] = ft_strlen(val);
	if (cwp[0] == 0 && cwp[2] == 0)
		return (oxx_zero(count, ((spec->fg[0]) ? 'O' : 'o'), val, cwp[1]));
	if (spec->fg[2])
	{
		if (spec->fg[0] && cwp[2] <= cwp[0])
			pc_di(count, '0', &(cwp[1]));
		oxx_left(count, val, cwp);
		return ;
	}
	o_right(count, cwp, spec);
	ft_putstr(val);
	*count += cwp[0];
	ft_strdel(&val);
}

void				route_oo(int *count, char f, va_list *ap, t_plist *spec)
{
	if (spec->jz[1] && f != 'O')
		cast_o(count, ft_itoa_base_su('o', (size_t)(va_arg(*ap, size_t)), 8), \
			spec);
	else if (spec->jz[0] && f != 'O')
		cast_o(count, ft_itoa_base_mu('o', (uintmax_t)(va_arg(*ap, \
			uintmax_t)), 8), spec);
	else if (spec->ll[1] && f != 'O')
		cast_o(count, ft_itoa_base_lu('o', (unsigned long long int)(va_arg(*ap\
			, unsigned long long int)), 8), spec);
	else if (spec->ll[0])
		cast_o(count, ft_itoa_base_lu('o', (unsigned long int)(va_arg(*ap, \
			unsigned long int)), 8), spec);
	else if (spec->hh[1] && f != 'O')
		cast_o(count, ft_itoa_base_lu('o', (unsigned char)(va_arg(*ap, \
			unsigned int)), 8), spec);
	else if (spec->hh[0] && f != 'O')
		cast_o(count, ft_itoa_base_lu('o', (unsigned short int)(va_arg(*ap, \
			unsigned int)), 8), spec);
	else if (f != 'O')
		cast_o(count, ft_itoa_base_lu('o', (unsigned int)(va_arg(*ap, \
			unsigned int)), 8), spec);
}
