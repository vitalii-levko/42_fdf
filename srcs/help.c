/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:18:05 by vlevko            #+#    #+#             */
/*   Updated: 2018/07/31 13:18:06 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	init_help(void)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		return (1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	return (0);
}

static int	get_response(void)
{
	char	c;

	attron(COLOR_PAIR(1));
	printw("Press 'c' to continue or 'q' to quit");
	refresh();
	attroff(COLOR_PAIR(1));
	while (1)
	{
		read(0, &c, 1);
		if (c == '\121' || c == '\161')
		{
			endwin();
			return (1);
		}
		if (c == '\103' || c == '\143')
			break ;
	}
	clear();
	move(0, 0);
	return (0);
}

static void	p_man(size_t *i, size_t j, char c, char *str)
{
	char	p;

	p = str[*i];
	*i += 1;
	if (*i < j)
	{
		c = str[*i];
		if (p == '/' && c == '*')
			attron(A_BOLD);
		else if (p == '*' && c == '/')
			attroff(A_BOLD);
		else if (p == '/' && c == '^')
			attron(COLOR_PAIR(1));
		else if (p == '^' && c == '/')
			attroff(COLOR_PAIR(1));
		else
		{
			printw("%c", p);
			return ;
		}
	}
	else
		printw("%c", p);
	*i += 1;
	refresh();
}

int			p_help(size_t i, size_t j, int fd, char c)
{
	int		row_col[2];
	int		y_x[2];
	char	*str;

	if (init_help())
		return (6);
	while (get_next_line(fd, &str) > 0)
	{
		getmaxyx(stdscr, row_col[0], row_col[1]);
		getyx(stdscr, y_x[0], y_x[1]);
		if (y_x[0] == (row_col[0] - 1))
		{
			if (get_response())
				return (0);
		}
		i = 0;
		j = ft_strlen(str);
		while (i < j)
			p_man(&i, j, '\0', str);
		printw("\n");
	}
	read(0, &c, 1);
	endwin();
	return (0);
}
