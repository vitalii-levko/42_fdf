/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:02:53 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:02:56 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <ncurses.h>
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# define WIDTH 1280
# define HEIGHT 720

typedef struct	s_struct
{

	long long int	max_z;
	long long int	min_z;
	int				init_width;
	int				init_height;
	double			scale;
	long long int	offset_x;
	long long int	reset_offset_x;
	long long int	offset_y;
	long long int	reset_offset_y;
	long long int	x;
	long long int	x2;
	long long int	x0;
	long long int	y;
	long long int	y2;
	long long int	y0;
	long long int	z1;
	long long int	z2;
	long long int	z0;
	long long int	tmp_x;
	long long int	tmp_y;
	long long int	tmp_z;
	long long int	tmp_x2;
	long long int	tmp_y2;
	long long int	tmp_z2;
	double			z;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	double			opacity;
	int				step_angle_x;
	int				step_angle_y;
	int				step_angle_z;
	int				sign_x;
	int				sign_y;
	long long int	delta;
	long long int	reset_delta;
	long long int	draw_dx;
	long long int	draw_dy;
	long long int	error;
	long long int	error2;
	long long int	step_y;
	long long int	step_x;
	double			step_z;
	int				step_move;
	int				tab;
	int				blank;
	int				fd;
	size_t			width;
	size_t			height;
	int				c1;
	int				c2;
	long long int	***map;
	void			*mlx;
	void			*win;
}				t_struct;

int				p_help(size_t i, size_t j, int fd, char c);

int				ret_fd(t_struct *fdf, int ret);

int				ret_f(t_struct *fdf, int ret, long long int ***curr);

int				ret_a(char ***arr, int ret, char **str);

void			reprint(t_struct *fdf);

void			p_info(t_struct *fdf, char *x, char *y, char *z);

int				p_err(int ret, char *str);

void			p_menu(t_struct *fdf);

int				print_line(t_struct *fdf, size_t i, size_t j);

int				save_map(t_struct *fdf, char *str, size_t h, size_t w);

int				init_fdf(t_struct *fdf, char *filepath);

int				deal_key(int key, t_struct *fdf);

void			scaling(int key, t_struct *fdf);

void			moving(int key, t_struct *fdf);

void			resetting(t_struct *fdf);

void			zooming(int key, t_struct *fdf);

void			tabulation(t_struct *fdf);

void			mov(long long int *x, long long int *y, long long int *z, \
				t_struct *fdf);

void			draw(t_struct *fdf, int new_c, double count_steps, \
				double step_x);

int				draw_point(t_struct *fdf, size_t i, size_t j);

int				check_max(t_struct *fdf, int cs);

int				save_color(t_struct *fdf, char *str, size_t i, size_t h);

void			save_z(t_struct *fdf, long long int nb);

char			**get_width(char *str, size_t *w);

#endif
