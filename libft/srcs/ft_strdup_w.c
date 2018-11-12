/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:10:41 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:42:25 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				cast_loc_two(wint_t c)
{
	unsigned int	mask;
	unsigned int	val;
	unsigned char	octet;
	unsigned char	bytes[2];

	mask = 49280;
	val = (unsigned int)(c);
	bytes[1] = (val << 26) >> 26;
	bytes[0] = ((val >> 6) << 27) >> 27;
	octet = (mask >> 8) | bytes[0];
	ft_putchar_w(octet);
	octet = ((mask << 24) >> 24) | bytes[1];
	ft_putchar_w(octet);
}

void				cast_loc_three(wint_t c)
{
	unsigned int	mask;
	unsigned int	val;
	unsigned char	octet;
	unsigned char	bytes[3];

	mask = 14712960;
	val = (unsigned int)(c);
	bytes[2] = (val << 26) >> 26;
	bytes[1] = ((val >> 6) << 26) >> 26;
	bytes[0] = ((val >> 12) << 28) >> 28;
	octet = (mask >> 16) | bytes[0];
	ft_putchar_w(octet);
	octet = ((mask << 16) >> 24) | bytes[1];
	ft_putchar_w(octet);
	octet = ((mask << 24) >> 24) | bytes[2];
	ft_putchar_w(octet);
}

static size_t		ft_strlen_w(const wchar_t *s)
{
	size_t			len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static wchar_t		*ft_strcpy_w(wchar_t *dst, const wchar_t *src)
{
	int				i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

wchar_t				*ft_strdup_w(const wchar_t *s1)
{
	wchar_t			*s2;

	if (!(s2 = (wchar_t *)malloc(sizeof(wchar_t) * (ft_strlen_w(s1) + 1))))
		return (NULL);
	ft_strcpy_w(s2, s1);
	return (s2);
}
