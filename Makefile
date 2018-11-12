# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 13:33:38 by vlevko            #+#    #+#              #
#    Updated: 2018/07/31 23:13:37 by vlevko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = fdf.c \
    srcs/draw.c \
    srcs/help.c \
    srcs/init.c \
    srcs/key.c \
    srcs/line.c \
    srcs/map.c \
    srcs/print.c \
    srcs/return.c \
    srcs/scale.c \
    srcs/transform.c \
    srcs/utils.c

OBJ = $(SRC:.c=.o)

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

LPATH = libft/

LFLAGS = -L libft/ -lft

LNFLAGS = -lncurses

GFLAGS = -lmlx -framework OpenGL -framework AppKit

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LPATH)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LFLAGS) $(LNFLAGS) $(GFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LPATH)
	@/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LPATH)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
