# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 19:18:13 by ltammie           #+#    #+#              #
#    Updated: 2020/03/23 06:41:37 by sauron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GCC = gcc -Wall -Wextra -Werror
NAME = fractol
SRCS = main.c
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
		$(GCC) $(OBJS) $(LIB) -o $(NAME) -lpthread

clean:
		rm -f $(OBJS)
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		make -C minilibx clean

re: fclean all
