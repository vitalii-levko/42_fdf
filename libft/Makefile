# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 13:33:38 by vlevko            #+#    #+#              #
#    Updated: 2018/04/08 15:50:16 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_isnum.c \
    ft_atoh.c \
    ft_arrdel.c \
    ft_itoa.c \
    ft_atoi.c \
	ft_isdigit.c \
	ft_isspace.c \
	ft_memalloc.c \
	ft_memset.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_strclr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strnew.c \
	ft_strsub.c \
	ft_printf.c \
	ft_strjoin.c \
	ft_strcat.c \
	get_next_line.c \
	ft_strsplit.c \
	ft_arrfree.c

SRCS = srcs/parse_ctrl.c \
	srcs/ft_itoa_base_slu_oxx.c \
	srcs/ft_strdup_w.c \
	srcs/cast_mdi.c \
	srcs/cast_ssdi.c \
	srcs/cast_hldi.c \
	srcs/cast_mu.c \
	srcs/cast_ws.c \
	srcs/cast_pc_w.c \
	srcs/route_di.c \
	srcs/route_uu.c \
	srcs/route_pxx.c \
	srcs/route_oo.c \
	srcs/route_ss.c \
	srcs/route_ecc.c

OBJ = $(SRC:.c=.o) $(SRCS:.c=.o)

INC = -I includes/

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -c

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
