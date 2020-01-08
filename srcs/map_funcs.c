/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:11:49 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/08 19:18:07 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

static void	add_texts(t_fdf *node)
{
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 10, 0xffffff,
		"KEYBOARD CONTROLS:");
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 30, 0xffffff,
		"PROJECTIONS: 1 = Isometric 30 degrees, 2 = Parallel top down");
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 50, 0xffffff,
		"MOVE: Arrow keys");
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 70, 0xffffff,
		"ZOOM: Numpad + and -");
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 90, 0xffffff,
		"DEPTH: Numpad * and /");
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 110, 0xffffff,
		"ROTATE XYZ: Numpad 4, 6, 2, 8, 1, 9");
	mlx_string_put(node->mlx_ptr, node->win_ptr, 10, 130, 0xffffff,
		"EXIT: Esc");
}

void		map_to_window(t_fdf *node)
{
	int		y;
	int		x;

	y = 0;
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
	mlx_put_image_to_window(node->mlx_ptr, node->win_ptr, node->img_ptr, 0, 0);
	add_texts(node);
}
