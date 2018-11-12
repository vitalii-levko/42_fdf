/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:26:47 by vlevko            #+#    #+#             */
/*   Updated: 2018/04/06 16:22:35 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

long long int	ft_atoi(const char *str)
{
	long long int	nb;
	int				sign;

	nb = 0;
	sign = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		str++;
		sign = 1;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		nb = nb * 10 + (int)*str - '0';
		str++;
	}
	if (sign)
		return (-nb);
	return (nb);
}
