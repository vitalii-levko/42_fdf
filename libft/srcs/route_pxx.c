/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_pxX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 23:12:52 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:54:10 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		oxx_left(int *count, char *val, int cwp[3])
{
	while ((cwp[2])-- > cwp[0])
		pc_di(count, '0', &(cwp[1]));
	ft_putstr(val);
	*count += cwp[0];
	cwp[1] -= cwp[0];
	while (cwp[1] > 0)
		pc_di(count, ' ', &(cwp[1]));
	ft_strdel(&val);
}

static void	xx_right(int *count, char c, int cwp[3], t_plist *spec)
{
	if ((spec->fg[0]) || c == 'p')
		cwp[1] -= 2;
	(cwp[2] > cwp[0]) ? (cwp[1] -= cwp[2]) : (cwp[1] -= cwp[0]);
	if (spec->wp[2])
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
	else
	{
		if (((spec->fg[0] && cwp[0] != 0) || c == 'p') && spec->fg[1])
		{
			ft_putstr((c == 'a' || c == 'p' ? "0x" : "0X"));
			*count += 2;
		}
		while (cwp[1] > 0)
			pc_di(count, ((spec->fg[1]) ? '0' : ' '), &(cwp[1]));
	}
	if (((spec->fg[0] && cwp[0] != 0) || c == 'p') && spec->fg[1] == 0)
	{
		ft_putstr((c == 'a' || c == 'p' ? "0x" : "0X"));
		*count += 2;
	}
	while (cwp[2] > cwp[0])
		pc_di(count, '0', &(cwp[2]));
}

static void	cast_xx(int *count, char c, char *val, t_plist *spec)
{
	int		cwp[3];

	cwp[0] = 0;
	(spec->wp[2] == 0) ? (spec->wp[1] = 1) : (cwp[0]);
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	cwp[0] = ft_strlen(val);
	if (cwp[0] == 0 && cwp[2] == 0)
		return (oxx_zero(count, c, val, cwp[1]));
	if (spec->fg[2])
	{
		if ((spec->fg[0] && cwp[0] != 0) || c == 'p')
		{
			ft_putstr((c == 'a' || c == 'p' ? "0x" : "0X"));
			cwp[1] -= 2;
			*count += 2;
		}
		oxx_left(count, val, cwp);
		return ;
	}
	xx_right(count, c, cwp, spec);
	ft_putstr(val);
	*count += cwp[0];
	ft_strdel(&val);
}

void		route_xx(int *count, char f, va_list *ap, t_plist *spec)
{
	if (spec->jz[1])
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_su((f == 'x' ? 'a' \
			: 'A'), (size_t)(va_arg(*ap, size_t)), 16), spec);
	else if (spec->jz[0])
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_mu((f == 'x' ? 'a' \
			: 'A'), (uintmax_t)(va_arg(*ap, uintmax_t)), 16), spec);
	else if (spec->ll[1])
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((f == 'x' ? 'a' \
			: 'A'), (unsigned long long int)(va_arg(*ap, \
				unsigned long long int)), 16), spec);
	else if (spec->ll[0])
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((f == 'x' ? 'a' \
			: 'A'), (unsigned long int)(va_arg(*ap, unsigned long int)), 16), \
	spec);
	else if (spec->hh[1])
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((f == 'x' ? 'a' \
			: 'A'), (unsigned char)(va_arg(*ap, unsigned int)), 16), spec);
	else if (spec->hh[0])
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((f == 'x' ? 'a' \
			: 'A'), (unsigned short int)(va_arg(*ap, unsigned int)), 16), spec);
	else
		cast_xx(count, (f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((f == 'x' ? 'a' \
			: 'A'), (unsigned int)(va_arg(*ap, unsigned int)), 16), spec);
}

void		route_p(int *count, char f, va_list *ap, t_plist *spec)
{
	spec->fg[0] = 1;
	cast_xx(count, f, ft_itoa_base_lu('a', (unsigned long int)(va_arg(*ap, \
		void *)), 16), spec);
}
