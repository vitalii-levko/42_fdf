/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_sS.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 00:23:09 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:42:43 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			count_bytes_w(unsigned long long int n)
{
	if (n <= 0x007F)
		return (1);
	else if (n <= 0x07FF)
		return (2);
	else if (n <= 0xFFFF)
		return (3);
	return (4);
}

static void	s_left(int *count, char *rt[2], int cwp[3], t_plist *spec)
{
	if (spec->wp[2])
	{
		rt[0] = ft_strsub(rt[1], 0, cwp[2]);
		cwp[1] -= ft_strlen(rt[0]);
		*count += ft_strlen(rt[0]);
	}
	else
	{
		cwp[1] -= cwp[0];
		rt[0] = ft_strdup(rt[1]);
		*count += cwp[0];
	}
	ft_putstr(rt[0]);
	ft_strdel(&(rt[0]));
	while (cwp[1] > 0)
		pc_di(count, ' ', &(cwp[1]));
}

static void	s_right(int *count, char *rt[2], int cwp[3], t_plist *spec)
{
	if (spec->wp[2])
	{
		rt[0] = ft_strsub(rt[1], 0, cwp[2]);
		cwp[1] -= ft_strlen(rt[0]);
		*count += ft_strlen(rt[0]);
	}
	else
	{
		cwp[1] -= cwp[0];
		rt[0] = ft_strdup(rt[1]);
		*count += cwp[0];
	}
	while (cwp[1] > 0)
		pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
	ft_putstr(rt[0]);
	ft_strdel(&(rt[0]));
}

static void	cast_s(int *count, char *str, t_plist *spec)
{
	char	*rt[2];
	int		cwp[3];

	rt[0] = NULL;
	rt[1] = NULL;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	if (str == NULL)
		rt[1] = ft_strdup("(null)");
	else
		rt[1] = ft_strdup(str);
	cwp[0] = 0;
	cwp[0] = ft_strlen(rt[1]);
	if (spec->fg[2])
		s_left(count, rt, cwp, spec);
	else
		s_right(count, rt, cwp, spec);
	ft_strdel(&(rt[1]));
}

void		route_ss(int *count, char f, va_list *ap, t_plist *spec)
{
	if (f == 's' || f == 'S')
	{
		if (spec->ll[0])
			cast_ws(count, va_arg(*ap, wchar_t *), spec);
		else
			cast_s(count, va_arg(*ap, char *), spec);
	}
}
