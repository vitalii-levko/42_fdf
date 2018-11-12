/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:14:39 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 14:14:40 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	ft_itoaifneg(int *n, int *count, size_t *i, char *str)
{
	if (*n < 0)
	{
		if (*n == -2147483648)
		{
			str[0] = '-';
			str[1] = '2';
			*n = 147483648;
			*count = *count / 10;
			*i = 2;
		}
		else
		{
			str[0] = '-';
			*i = 1;
			*n = -*n;
		}
	}
	else
		*i = 0;
}

static void	ft_itoacount(int *n, int *count, size_t *i)
{
	if (*n < 0)
		*n = -*n;
	while (*n / 10)
	{
		*count = *count * 10;
		*i = *i + 1;
		*n = *n / 10;
	}
}

char		*ft_itoa(int n)
{
	int		count;
	int		tmp;
	char	*str;
	size_t	i;

	count = 1;
	i = 1;
	tmp = n;
	if (n < 0)
		i++;
	ft_itoacount(&n, &count, &i);
	if (!(str = ft_strnew(i)))
		return (NULL);
	ft_itoaifneg(&tmp, &count, &i, str);
	while (count / 10)
	{
		str[i] = (char)((tmp / count) + '0');
		tmp = tmp % count;
		count = count / 10;
		i++;
	}
	str[i] = (char)(tmp + '0');
	return (str);
}
