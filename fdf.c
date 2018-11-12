/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:57:57 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/29 22:28:56 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static int	check_dir(char *str)
{
	int		fd;

	fd = open(str, O_DIRECTORY);
	if (fd == -1)
		fd = open(str, O_RDONLY);
	else
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

static int	check_args(int ac, char **av, t_struct **fdf, int fd)
{
	int		ret;

	if (ac == 2 && !ft_strcmp("--help", av[1]))
	{
		fd = open("man/Fdf.man", O_RDONLY);
		if (fd == -1)
			exit(p_err(1, "Cannot access the man file"));
		ret = p_help(0, 0, fd, '\0');
		close(fd);
		exit(ret);
	}
	else if (ac == 2)
	{
		if (!(*fdf = (t_struct *)ft_memalloc(sizeof(t_struct))))
			exit(p_err(2, "Memory allocation failed"));
		(*fdf)->map = NULL;
		(*fdf)->mlx = NULL;
		(*fdf)->win = NULL;
		(*fdf)->fd = check_dir(av[1]);
		if ((*fdf)->fd == -1)
			exit(ret_f(*fdf, p_err(3, "Cannot access the map file"), NULL));
		return (1);
	}
	return (ret_f(*fdf, 0, NULL));
}

static void	new_win(t_struct **fdf, char *str)
{
	if (WIDTH > 2560)
		(*fdf)->init_width = 2560;
	else if (WIDTH < 500)
		(*fdf)->init_width = 640;
	else
		(*fdf)->init_width = WIDTH;
	if (HEIGHT > 1440)
		(*fdf)->init_height = 1440;
	else if (HEIGHT < 500)
		(*fdf)->init_height = 480;
	else
		(*fdf)->init_height = HEIGHT;
	(*fdf)->win = mlx_new_window((*fdf)->mlx, (*fdf)->init_width, \
	(*fdf)->init_height, str);
}

static int	ext(void)
{
	exit(0);
	return (0);
}

int			main(int ac, char **av)
{
	t_struct	*fdf;

	fdf = NULL;
	if (check_args(ac, av, &fdf, -1))
	{
		fdf->mlx = mlx_init();
		if (!fdf->mlx)
			return (ret_fd(fdf, p_err(4, "Mlx init function failed")));
		new_win(&fdf, av[1]);
		if (!fdf->win)
			return (ret_fd(fdf, p_err(5, "Mlx new window function failed")));
		if (init_fdf(fdf, av[1]) || save_map(fdf, NULL, 0, 0))
			return (ret_fd(fdf, 7));
		mlx_hook(fdf->win, 2, 5, deal_key, fdf);
		mlx_hook(fdf->win, 17, (1L << 17), ext, fdf);
		mlx_loop(fdf->mlx);
	}
	else
		printf("usage: ./fdf --help | map_source_file\n");
	return (0);
}
