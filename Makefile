# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/01 15:07:10 by ltammie           #+#    #+#              #
#    Updated: 2020/08/04 13:11:24 by ltammie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc -Wall -Wextra -Werror
NAME = fractol
SRCS = src/main.c\
		src/cl_init.c\
		src/coloring.c\
		src/controls.c\
		src/controls_2.c\
		src/controls_3.c\
		src/controls_4.c\
		src/controls_5.c\
		src/draw.c\
		src/error.c\
		src/init_data.c\
		src/rgb.c

OBJS = $(SRCS:.c=.o)
HEAD = -c -I fractol.h
LIB = -L libft -lft -L minilibx -lmlx -Wdeprecated-declarations   -framework OpenGL -framework Appkit -framework OpenCL

all: $(NAME)

src%.o: %.c
		$(GCC) -c $<

lib:
		make -C libft
		make -C minilibx

$(NAME): $(OBJS) lib
		$(GCC) $(OBJS) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJS)
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		make -C minilibx clean

re: fclean all
