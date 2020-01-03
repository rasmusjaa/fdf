/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:11:49 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/03 13:17:24 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
// yhdista
#include "fdf.h"

static int	get_height(char *str)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	while (ft_get_next_line(fd, &line) > 0)
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

static int	get_width(char *str)
{
	int		fd;
	int		words;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	if (ft_get_next_line(fd, &line) < 1)
		return (-1);
	words = ft_count_words(line, ' ');
	free(line);
	close(fd);
	return (words);
}

int			get_map(char *str, t_fdf *node)
{
	int i;
	int j;

	i = 0;
	node->height = get_height(str);
	node->width = get_width(str);
	if (node->height < 1 || node->width < 1 || get_grid(str, node) != 0)
		return (-1);
	ft_printf("Map (height %d & width %d):\n", node->height, node->width);
	while (i < node->height)
	{
		j = 0;
		while (j < node->width)
		{
			ft_printf("%4d", node->grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}

	return (0);
}

static void	add_texts(t_fdf *node)
{
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  10,  0xffffff,
		"KEYBOARD CONTROLS:");
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  30,  0xffffff,
		"PROJECTIONS: 1 = Isometric 30 degrees, 2 = Parallel top down");
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  50,  0xffffff,
		"MOVE: Arrow keys");
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  70,  0xffffff,
		"ZOOM: Numpad + and -");
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  90,  0xffffff,
		"DEPTH: Numpad * and /");
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  110,  0xffffff,
		"ROTATE XYZ: Numpad 4, 6, 2, 8, 1, 9");
	mlx_string_put(node->mlx_ptr, node->win_ptr,  10,  130,  0xffffff,
		"EXIT: Esc");
}

void		map_to_window(t_fdf *node)
{
	int		y;
	int		x;

	y = 0;
	add_texts(node);
	while (y < node->height)
	{
		x = 0;
		while (x < node->width)
		{
			if (x < node->width - 1)
				bresenham_x(x, y, node);
			if (y < node->height - 1)
				bresenham_y(x, y, node);
			x++;
		}
		y++;
	}
}
