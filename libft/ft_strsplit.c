/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:10:02 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/05 23:50:05 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_chrcnt(const char *s, char c, size_t *pos)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[*pos])
	{
		if (s[*pos] == c)
		{
			while (s[*pos] == c)
				*pos = *pos + 1;
			break ;
		}
		*pos = *pos + 1;
		i++;
	}
	return (i);
}

static char		*ft_chrtrim(char const *s, char c, char **str, size_t i)
{
	size_t	len;
	size_t	tmp;
	size_t	start;

	if (str)
		ft_strdel(str);
	len = 0;
	while (s[i] == c)
		i++;
	start = i;
	while (s[i] != '\0')
	{
		tmp = i;
		if (s[i] == c)
			while (s[i] == c)
				i++;
		if (tmp != i && s[i] != '\0')
			len += i - tmp;
		else if (s[i] != '\0')
		{
			len++;
			i++;
		}
	}
	return (ft_strsub(s, start, len));
}

static size_t	ft_arrlen(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			count++;
			while (str[i] == c)
				i++;
		}
		else
			i++;
	}
	if (count || i)
		count++;
	return (count);
}

static char		**ft_isnull(char **str)
{
	char	**arr;

	if (str)
		ft_strdel(str);
	if (!(arr = (char **)malloc(sizeof(char **))))
		return (NULL);
	if (!(arr[0] = (char *)malloc(sizeof(char *))))
	{
		free(arr);
		return (NULL);
	}
	ft_strcpy(arr[0], "\0");
	return (arr);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	char	*str;
	size_t	i;
	size_t	sp[2];

	i = 0;
	sp[0] = 0;
	sp[1] = 0;
	if (!s || !c)
		return (ft_isnull(NULL));
	str = ft_chrtrim(s, c, NULL, 0);
	if (!(arr = (char **)malloc(sizeof(char **) * (ft_arrlen(str, c) + 1))))
		return (ft_isnull(&str));
	while (i++ < ft_arrlen(str, c))
	{
		if (!(arr[i - 1] = ft_strsub(str, sp[0], ft_chrcnt(str, c, &(sp[1])))))
		{
			ft_strdel(&str);
			return (ft_arrfree(arr, i - 1));
		}
		sp[0] = sp[1];
	}
	arr[ft_arrlen(str, c)] = NULL;
	ft_strdel(&str);
	return (arr);
}
