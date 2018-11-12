/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:29:01 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:29:03 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	p_half_menu(t_struct *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width / 2 - 20, 0, 0xffffff, \
	"menu");
	mlx_string_put(fdf->mlx, fdf->win, 5, 40, 0xffffff, "move toward:");
	mlx_string_put(fdf->mlx, fdf->win, 5, 60, 0x66cccc, \
	"   top   left   down   right");
	mlx_string_put(fdf->mlx, fdf->win, 5, 80, 0x66cc66, \
	"   'up'  'left' 'down' 'right'");
	mlx_string_put(fdf->mlx, fdf->win, 5, 120, 0xffffff, "rotate toward:");
	mlx_string_put(fdf->mlx, fdf->win, 5, 140, 0x66cccc, \
	"   top   left   down   right   clockwise   counterclockwise");
	mlx_string_put(fdf->mlx, fdf->win, 5, 160, 0x66cc66, \
	"   'w'   'a'    'step_move'    'd'     'e'         'q'");
	mlx_string_put(fdf->mlx, fdf->win, 5, 200, 0xffffff, "scale:");
	mlx_string_put(fdf->mlx, fdf->win, 5, 220, 0x66cccc, "   in   out");
	mlx_string_put(fdf->mlx, fdf->win, 5, 240, 0x66cc66, "   'i'  'o'");
}

void		p_menu(t_struct *fdf)
{
	p_half_menu(fdf);
	mlx_string_put(fdf->mlx, fdf->win, 5, 280, 0xffffff, "altitude:");
	mlx_string_put(fdf->mlx, fdf->win, 5, 300, 0x66cccc, \
	"   increase   decrease  ");
	mlx_string_put(fdf->mlx, fdf->win, 5, 320, 0x66cc66, \
	"   'enter'    'space'  ");
	mlx_string_put(fdf->mlx, fdf->win, 5, 360, 0xffffff, "hotkeys:");
	mlx_string_put(fdf->mlx, fdf->win, 5, 380, 0x66cccc, \
	"   menu   reset   blank   exit");
	mlx_string_put(fdf->mlx, fdf->win, 5, 400, 0x66cc66, \
	"   'tab'  'r'     'b'     'esc'");
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width - 165, \
	fdf->init_height - 24, 0x66cccc, "(c) vlevko, 2018");
	mlx_string_put(fdf->mlx, fdf->win, 5, fdf->init_height - 24, 0x66cccc, \
	"UNIT Factory");
}

int			p_err(int ret, char *str)
{
	ft_printf("ERROR: %s\n", str);
	return (ret);
}

void		p_info(t_struct *fdf, char *x, char *y, char *z)
{
	char	*s;

	x = ft_itoa(fdf->step_angle_x);
	y = ft_itoa(fdf->step_angle_y);
	z = ft_itoa(fdf->step_angle_z);
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width - 136, 0, 0x66cccc, \
	"axis   degree");
	s = ft_strjoin("x:     ", x);
	ft_strdel(&x);
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width - 136, 20, 0x66cc66, s);
	ft_strdel(&s);
	s = ft_strjoin("y:     ", y);
	ft_strdel(&y);
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width - 136, 40, 0x66cc66, s);
	ft_strdel(&s);
	s = ft_strjoin("z:     ", z);
	ft_strdel(&z);
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width - 136, 60, 0x66cc66, s);
	ft_strdel(&s);
	mlx_string_put(fdf->mlx, fdf->win, 5, 0, 0x66cccc, "menu");
	mlx_string_put(fdf->mlx, fdf->win, 5, 20, 0x66cc66, "'tab'");
	mlx_string_put(fdf->mlx, fdf->win, fdf->init_width - 165, \
	fdf->init_height - 24, 0x66cccc, "(c) vlevko, 2018");
	mlx_string_put(fdf->mlx, fdf->win, 5, fdf->init_height - 24, 0x66cccc, \
	"UNIT Factory");
}

void		reprint(t_struct *fdf)
{
	size_t	i;

	mlx_clear_window(fdf->mlx, fdf->win);
	fdf->step_y = fdf->reset_delta;
	i = 0;
	while (i < fdf->height)
	{
		if (print_line(fdf, i, 0))
			exit(7);
		i++;
	}
	p_info(fdf, NULL, NULL, NULL);
}
