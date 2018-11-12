/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_pc_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:30:33 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:37:58 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			cast_loc_four(wint_t c)
{
	unsigned int	mask;
	unsigned int	val;
	unsigned char	octet;
	unsigned char	bytes[4];

	mask = 4034953344;
	val = (unsigned int)(c);
	bytes[3] = (val << 26) >> 26;
	bytes[2] = ((val >> 6) << 26) >> 26;
	bytes[1] = ((val >> 12) << 26) >> 26;
	bytes[0] = ((val >> 18) << 29) >> 29;
	octet = (mask >> 24) | bytes[0];
	ft_putchar_w(octet);
	octet = ((mask << 8) >> 24) | bytes[1];
	ft_putchar_w(octet);
	octet = ((mask << 16) >> 24) | bytes[2];
	ft_putchar_w(octet);
	octet = ((mask << 24) >> 24) | bytes[3];
	ft_putchar_w(octet);
}

void				ft_putstr_w(int len, wchar_t const *s)
{
	int				bytes;

	bytes = 0;
	if (s)
		while (*s != '\0')
		{
			bytes = count_bytes_w(*s);
			if (len - bytes < 0)
				break ;
			len -= bytes;
			if (bytes == 1)
				ft_putchar_w((unsigned char)(*s));
			else if (bytes == 2)
				cast_loc_two(*s);
			else if (bytes == 3)
				cast_loc_three(*s);
			else
				cast_loc_four(*s);
			s++;
		}
}

static void			pc_w_left(int *count, int wid, int size, wint_t c)
{
	if (size == 1)
	{
		c = (unsigned char)(c);
		ft_putchar_w(c);
	}
	else if (size == 2)
		cast_loc_two(c);
	else if (size == 3)
		cast_loc_three(c);
	else if (size == 4)
		cast_loc_four(c);
	if (wid > size)
		*count += wid;
	else
		*count += size;
	while (wid-- > size)
		ft_putchar(' ');
}

static void			pc_w_right(int *count, int ws[2], wint_t c, t_plist *spec)
{
	if (ws[0] > ws[1])
		*count += ws[0];
	else
		*count += ws[1];
	while (ws[0]-- > ws[1])
		ft_putchar((spec->fg[1] ? '0' : ' '));
	if (ws[1] == 1)
	{
		c = (unsigned char)(c);
		ft_putchar_w(c);
	}
	else if (ws[1] == 2)
		cast_loc_two(c);
	else if (ws[1] == 3)
		cast_loc_three(c);
	else if (ws[1] == 4)
		cast_loc_four(c);
}

void				cast_pc_w(int *count, wint_t c, t_plist *spec)
{
	int				ws[2];

	ws[1] = 0;
	ws[1] = count_bytes_w(c);
	ws[0] = spec->wp[0];
	if (ws[1] != 1 && MB_CUR_MAX < ws[1])
		ws[1] = 1;
	if (c == 0)
	{
		while ((ws[0])-- > 1)
			pc_di(count, ((spec->fg[1]) ? '0' : ' '), 0);
		pc_di(count, '\0', 0);
		return ;
	}
	if (spec->fg[2])
		pc_w_left(count, ws[0], ws[1], c);
	else
		pc_w_right(count, ws, c, spec);
}
