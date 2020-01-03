# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 15:06:49 by rjaakonm          #+#    #+#              #
#    Updated: 2019/12/19 15:31:32 by rjaakonm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS =	main.c \
		map_funcs.c \
		number_grid.c \
		projections.c \
		draw.c \
		help_funcs.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

LIB = -L ./libft -lft -lmlx -framework OpenGL -framework AppKit
# -L ./minilibx/

INCL = -I ./incl -I ./libft/libft/incl/ -I ./libft/printf/incl/

.PHONY: all clean fclean re run run2

all: $(NAME)

$(NAME): libftmake
	gcc $(FLAGS) -c $(SRCS) $(INCL)
	gcc $(FLAGS) $(INCL) $(OBJS) $(LIB) -o $(NAME)

libftmake:
	@make -C libft

clean:
#	@rm -f $(notdir $(OBJS))
	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	gcc $(FLAGS) -c $(SRCS) $(INCL)
	gcc $(FLAGS) $(INCL) $(OBJS) $(LIB) -o $(NAME)
	./fdf test_maps/42.fdf
