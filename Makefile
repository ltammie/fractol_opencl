GCC = gcc -Wall -Wextra -Werror
NAME = fractol
SRCS = main.c\
		cl_init.c\
		coloring.c\
		controls.c\
		controls_2.c\
		controls_3.c\
		draw.c\
		error.c\
		init_data.c\
		rgb.c

OBJS = $(SRCS:.c=.o)
HEAD = -c -I fractol.h
LIB = -L libft -lft -L minilibx -lmlx -Wdeprecated-declarations   -framework OpenGL -framework Appkit -framework OpenCL

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
