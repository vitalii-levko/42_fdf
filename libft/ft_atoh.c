/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:19:29 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 14:19:31 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		get_base(const char c)
{
	int		nb;

	if (c >= '0' && c <= '9')
		nb = c - '0';
	else if (c >= 'a' && c <= 'z')
		nb = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		nb = c - 'A' + 10;
	else
		nb = -1;
	return (nb);
}

int		ft_atoh(const char *str, int base)
{
	int		neg;
	int		nbr;
	int		curr;

	neg = 0;
	nbr = 0;
	if (*str == '-')
		neg++;
	if (*str == '-' || *str == '+')
		str++;
	curr = get_base(*str);
	while (curr >= 0 && curr < base)
	{
		nbr = nbr * base + curr;
		str++;
		curr = get_base(*str);
	}
	if (neg)
		nbr = -nbr;
	return (nbr);
}
