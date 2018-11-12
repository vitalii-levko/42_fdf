/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:47:54 by vlevko            #+#    #+#             */
/*   Updated: 2018/04/08 16:24:18 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_isnum(char *str);

int					ft_atoh(const char *str, int base);

void				ft_arrdel(char ***arr);

char				*ft_itoa(int n);

char				**ft_arrfree(char **arr, size_t i);

char				**ft_strsplit(char const *s, char c);

long long int		ft_atoi(const char *str);

int					ft_isdigit(int c);

void				*ft_memalloc(size_t size);

void				*ft_memset(void *b, int c, size_t len);

void				ft_putchar(char c);

void				ft_putstr(char const *s);

char				*ft_strcat(char *restrict s1, const char *restrict s2);

void				ft_strclr(char *s);

int					ft_strcmp(const char *s1, const char *s2);

char				*ft_strcpy(char *dst, const char *src);

void				ft_strdel(char **as);

char				*ft_strdup(const char *s1);

char				*ft_strjoin(char const *s1, char const *s2);

size_t				ft_strlen(const char *s);

char				*ft_strnew(size_t size);

char				*ft_strsub(char const *s, unsigned int start, size_t len);

int					ft_isspace(int c);

int					ft_printf(const char *format, ...);

#endif
