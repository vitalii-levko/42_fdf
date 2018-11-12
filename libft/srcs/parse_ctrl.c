/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:37:07 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 12:09:55 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ctrl_init(t_plist *spec)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		spec->fg[i] = 0;
		if (i < 2)
		{
			spec->wp[i] = 0;
			spec->hh[i] = 0;
			spec->ll[i] = 0;
			spec->jz[i] = 0;
		}
		if (i == 2)
			spec->wp[i] = 0;
	}
}

static void	ctrl_wp(t_plist *spec, const char **f, int i)
{
	char	*str;

	str = NULL;
	if (**f == '.')
	{
		(*f)++;
		if (**f == '-')
			(*f)++;
		while (ft_isdigit((*f)[i]))
			i++;
		str = ft_strsub(*f, 0, i);
		spec->wp[2] = 1;
		spec->wp[1] = ft_atoi(str);
	}
	else
	{
		while (ft_isdigit((*f)[i]))
			i++;
		str = ft_strsub(*f, 0, i);
		spec->wp[0] = ft_atoi(str);
	}
	ft_strdel(&str);
	while (i-- > 0)
		(*f)++;
}

static void	ctrl_hl(t_plist *spec, const char **f)
{
	if (**f == 'h')
	{
		(*f)++;
		if (**f == 'h')
		{
			(*f)++;
			spec->hh[1] = 1;
		}
		else
			spec->hh[0] = 1;
		return ;
	}
	(*f)++;
	if (**f == 'l')
	{
		(*f)++;
		spec->ll[1] = 1;
	}
	else
		spec->ll[0] = 1;
}

static void	ctrl_fg(t_plist *spec, const char **f)
{
	if (**f == '#')
	{
		spec->fg[0] = 1;
		(*f)++;
	}
	if (**f == '0')
	{
		spec->fg[1] = 1;
		(*f)++;
	}
	if (**f == '-')
	{
		spec->fg[2] = 1;
		(*f)++;
	}
	if (**f == ' ')
	{
		spec->fg[3] = 1;
		(*f)++;
	}
	if (**f == '+')
	{
		spec->fg[4] = 1;
		(*f)++;
	}
}

void		parse_ctrl(t_plist *spec, const char **f, t_pflist *pfc)
{
	ctrl_init(spec);
	while (ft_chrseek(pfc->ctrl, **f, 0) || ft_isdigit(**f))
	{
		if ((**f >= '1' && **f <= '9') || **f == '.')
			ctrl_wp(spec, f, 0);
		if (**f == 'h' || **f == 'l')
			ctrl_hl(spec, f);
		while (ft_chrseek("#0- +", **f, 0))
			ctrl_fg(spec, f);
		if (**f == 'L' || **f == 't')
			(*f)++;
		if (**f == 'j' || **f == 'z')
		{
			if (**f == 'j')
				spec->jz[0] = 1;
			else
				spec->jz[1] = 1;
			(*f)++;
		}
	}
}
