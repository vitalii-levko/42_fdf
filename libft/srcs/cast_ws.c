/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ws.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:00:42 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:08:15 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	ft_cntlen_w(int prec, const wchar_t *res)
{
	size_t			cnt;
	unsigned int	size;

	cnt = 0;
	while (*res != '\0')
	{
		size = count_bytes_w(*res);
		if (prec != -1 && size + cnt > (unsigned int)(prec))
			break ;
		cnt += size;
		res++;
	}
	return (cnt);
}

static void		ws_left(int *count, int cwp[3], wchar_t *res)
{
	if (cwp[2] == 0)
	{
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
		return ;
	}
	cwp[1] -= cwp[0];
	*count += cwp[0];
	ft_putstr_w(cwp[0], res);
	while (cwp[1] > 0)
		pc_di(count, ' ', &(cwp[1]));
}

static void		ws_right(int *count, int cwp[3], wchar_t *res, t_plist *spec)
{
	if (cwp[2] == 0)
	{
		while (cwp[1] > 0)
			pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
		return ;
	}
	cwp[1] -= cwp[0];
	*count += cwp[0];
	while (cwp[1] > 0)
		pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
	ft_putstr_w(cwp[0], res);
}

static void		ft_strdel_w(wchar_t **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}

void			cast_ws(int *count, wchar_t *str, t_plist *spec)
{
	int				cwp[3];
	wchar_t			*res;

	res = NULL;
	cwp[1] = spec->wp[0];
	if (str == NULL)
		res = ft_strdup_w(L"(null)");
	else
		res = ft_strdup_w(str);
	cwp[0] = 0;
	if (spec->wp[2])
		cwp[2] = spec->wp[1];
	else
		cwp[2] = -1;
	cwp[0] = ft_cntlen_w(cwp[2], res);
	if (spec->fg[2])
		ws_left(count, cwp, res);
	else
		ws_right(count, cwp, res, spec);
	ft_strdel_w(&res);
}
