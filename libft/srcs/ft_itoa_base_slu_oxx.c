/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_slu_oxX.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 22:07:00 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:56:50 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void							oxx_zero(int *count, char c, char *val, int wid)
{
	if (c == 'p')
		wid -= 2;
	while (wid > 0)
		pc_di(count, ' ', &wid);
	if (c == 'p')
	{
		ft_putstr("0x");
		*count += 2;
	}
	else if (c == 'O')
	{
		ft_putchar('0');
		(*count)++;
	}
	ft_strdel(&val);
}

static size_t					ft_pow_su(int nbr, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (size_t)(nbr * ft_pow_su(nbr, pow - 1));
}

char							*ft_itoa_base_su(char c, size_t val, int base)
{
	int							i;
	char						*str;

	i = 1;
	str = NULL;
	while (ft_pow_su(base, i) - 1 < val)
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

static unsigned long long int	ft_pow_lu(int nbr, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (unsigned long long int)(nbr * ft_pow_lu(nbr, pow - 1));
}

char							*ft_itoa_base_lu(char c, unsigned long long \
	int val, int base)
{
	int							i;
	char						*str;

	i = 1;
	str = NULL;
	while (ft_pow_lu(base, i) - 1 < val)
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
