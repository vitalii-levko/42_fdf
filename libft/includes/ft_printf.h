/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 21:12:11 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/28 13:45:27 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <limits.h>
# include <stdint.h>
# include <wchar.h>
# include <stdarg.h>
# include "libft.h"
# define SNUM 8

typedef struct	s_plist
{
	int			fg[5];
	int			wp[3];
	int			hh[2];
	int			ll[2];
	int			jz[2];
}				t_plist;

typedef struct	s_pflist
{
	char		*ctrl;
	char		*capital;
	char		**form;
	void		(*pf[SNUM])(int *, char, va_list *, t_plist *);
}				t_pflist;

void			pc_di(int *count, char c, int *dec);

void			ft_putnbr_m(int minval, intmax_t nbr);

void			ft_putnbr_ll(int minval, long long int nbr);

void			ft_putnbr_ss(int minval, ssize_t nbr);

void			ssmhldi_zero(int *count, int wid, t_plist *spec);

int				ft_chrseek(const char *s, char c, int i);

void			ft_putchar_w(wint_t c);

void			ft_putstr_w(int len, wchar_t const *s);

wchar_t			*ft_strdup_w(const wchar_t *s1);

char			*ft_itoa_base_mu(char c, uintmax_t val, int base);

char			*ft_itoa_base_su(char c, size_t val, int base);

char			*ft_itoa_base_lu(char c, unsigned long long int val, int base);

void			cast_mdi(int *count, intmax_t val, t_plist *spec);

void			cast_ssdi(int *count, ssize_t val, t_plist *spec);

void			cast_hldi(int *count, long long int val, t_plist *spec);

void			oxx_zero(int *count, char c, char *val, int wid);

void			oxx_left(int *count, char *val, int cwp[3]);

void			mslu_zero(int *count, int wid);

void			mslu_left(int *count, int cwp[3]);

void			mslu_rt(int *count, int cwp[3], t_plist *spec);

void			cast_mu(int *count, uintmax_t val, t_plist *spec);

void			parse_ctrl(t_plist *spec, const char **f, t_pflist *pfc);

void			cast_loc_two(wint_t c);

void			cast_loc_three(wint_t c);

int				count_bytes_w(unsigned long long int n);

void			cast_pc_w(int *count, wint_t c, t_plist *spec);

void			cast_ws(int *count, wchar_t *str, t_plist *spec);

void			route_di(int *count, char f, va_list *ap, t_plist *spec);

void			route_uu(int *count, char f, va_list *ap, t_plist *spec);

void			route_oo(int *count, char f, va_list *ap, t_plist *spec);

void			route_xx(int *count, char f, va_list *ap, t_plist *spec);

void			route_p(int *count, char f, va_list *ap, t_plist *spec);

void			route_ss(int *count, char f, va_list *ap, t_plist *spec);

void			route_cc(int *count, char f, va_list *ap, t_plist *spec);

void			route_e(int *count, char f, va_list *ap, t_plist *spec);

#endif
