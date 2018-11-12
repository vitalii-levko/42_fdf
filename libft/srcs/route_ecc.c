/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_ecC.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 00:00:00 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:40:53 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_putchar_w(wint_t c)
{
	write(1, &c, 1);
}

void		pc_di(int *count, char c, int *dec)
{
	ft_putchar(c);
	if (dec)
		(*dec)--;
	(*count)++;
}

static void	cast_pc(int *count, char c, t_plist *spec)
{
	int		wid;

	wid = spec->wp[0];
	if (c == 0)
	{
		while (wid-- > 1)
			pc_di(count, ((spec->fg[1] && !spec->fg[2]) ? '0' : ' '), 0);
		pc_di(count, '\0', 0);
		return ;
	}
	if (spec->fg[2])
	{
		pc_di(count, c, 0);
		while (wid-- > 1)
			pc_di(count, ' ', 0);
	}
	else
	{
		while (wid-- > 1)
			(spec->fg[1]) ? (pc_di(count, '0', 0)) : (pc_di(count, ' ', 0));
		pc_di(count, c, 0);
	}
}

void		route_cc(int *count, char f, va_list *ap, t_plist *spec)
{
	if (f == 'c' || f == 'C')
	{
		if (spec->ll[0])
			cast_pc_w(count, (wint_t)(va_arg(*ap, wint_t)), spec);
		else
			cast_pc(count, (unsigned char)(va_arg(*ap, int)), spec);
	}
	else if (f == '%')
		cast_pc(count, f, spec);
}

void		route_e(int *count, char f, va_list *ap, t_plist *spec)
{
	if (f != '\0')
		cast_pc(count, f, spec);
	else if (*ap)
		return ;
}
