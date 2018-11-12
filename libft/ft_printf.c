/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 22:18:36 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:42:53 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static int		print_c(int *count, char c)
{
	if (c != '%')
	{
		ft_putchar(c);
		(*count)++;
		return (1);
	}
	return (-1);
}

static int		pfc_init(t_pflist **pfc, int i)
{
	*pfc = (t_pflist *)malloc(sizeof(t_pflist));
	(*pfc)->form = (char **)malloc(sizeof(char *) * SNUM);
	(*pfc)->ctrl = ft_strdup("#0- +lhjzLt.");
	(*pfc)->capital = ft_strdup("DOUSC");
	(*pfc)->form[SNUM - i--] = ft_strdup("diD");
	(*pfc)->form[SNUM - i--] = ft_strdup("cC%");
	(*pfc)->form[SNUM - i--] = ft_strdup("uU");
	(*pfc)->form[SNUM - i--] = ft_strdup("xX");
	(*pfc)->form[SNUM - i--] = ft_strdup("oO");
	(*pfc)->form[SNUM - i--] = ft_strdup("sS");
	(*pfc)->form[SNUM - i--] = ft_strdup("p");
	(*pfc)->form[SNUM - i--] = ft_strdup(" ");
	i = SNUM;
	(*pfc)->pf[SNUM - i--] = &route_di;
	(*pfc)->pf[SNUM - i--] = &route_cc;
	(*pfc)->pf[SNUM - i--] = &route_uu;
	(*pfc)->pf[SNUM - i--] = &route_xx;
	(*pfc)->pf[SNUM - i--] = &route_oo;
	(*pfc)->pf[SNUM - i--] = &route_ss;
	(*pfc)->pf[SNUM - i--] = &route_p;
	(*pfc)->pf[SNUM - i--] = &route_e;
	return (0);
}

static int		ftp_free(int count, t_pflist *pfc, t_plist *spec)
{
	int			i;

	i = -1;
	if (pfc)
	{
		while (++i < SNUM)
		{
			free(pfc->form[i]);
			pfc->form[i] = NULL;
		}
		free(pfc->form);
		pfc->form = NULL;
		free(pfc->capital);
		pfc->capital = NULL;
		free(pfc->ctrl);
		pfc->ctrl = NULL;
		free(pfc);
		pfc = NULL;
	}
	if (spec)
	{
		free(spec);
		spec = NULL;
	}
	return (count);
}

int				ft_chrseek(const char *s, char c, int i)
{
	if (i == SNUM - 1 && *s == ' ' && c != '\0')
		return (1);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ci[2];
	t_plist		*spec;
	t_pflist	*pfc;

	pfc = NULL;
	ci[0] = pfc_init(&pfc, SNUM);
	spec = (t_plist *)malloc(sizeof(t_plist));
	va_start(ap, format);
	while (*format)
	{
		if ((ci[1] = print_c(&(ci[0]), *format++)) == 1)
			continue ;
		parse_ctrl(spec, &format, pfc);
		if (ft_chrseek(pfc->capital, *format, ci[1]))
			spec->ll[0] = 1;
		while (++(ci[1]) < SNUM)
			if (ft_chrseek(pfc->form[ci[1]], *format, ci[1]))
			{
				(*(pfc->pf[ci[1]]))(&(ci[0]), *format, &ap, spec);
				break ;
			}
		(*format != '\0') ? format++ : va_end(ap);
	}
	return (ftp_free(ci[0], pfc, spec));
}
