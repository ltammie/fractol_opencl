# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 19:18:13 by ltammie           #+#    #+#              #
#    Updated: 2020/04/03 14:25:55 by sauron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GCC = gcc -Wall -Wextra -Werror
NAME = fractol
SRCS = main.c\
		controls.c\
		init_data.c\
		error.c\
		draw.c\
		cl_init.c
OBJS = $(SRCS:.c=.o)
HEAD = -c -I fractol.h
LIB = -L libft -lft -L minilibx -lmlx -framework OpenGL -framework Appkit -framework OpenCL

all: $(NAME)

%.o: %.c
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
