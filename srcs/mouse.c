/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:57:12 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/13 11:57:56 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int			mouse_move(int x, int y, t_fdf *node)
{
	if (node->mouse_1 == 1)
	{
		node->move_x -= node->mouse_x - x;
		node->move_y -= node->mouse_y - y;
		node->mouse_x = x;
		node->mouse_y = y;
	}
	if (node->mouse_2 == 1)
	{
		node->rot_x -= (node->mouse_y - y) / 3;
		node->rot_y -= (node->mouse_x - x) / 3;
		node->mouse_x = x;
		node->mouse_y = y;
	}
	mlx_destroy_image(node->mlx_ptr, node->img_ptr);
	node->img_ptr = mlx_new_image(node->mlx_ptr, WINDOW_X, WINDOW_Y);
	mlx_clear_window(node->mlx_ptr, node->win_ptr);
	map_to_window(node);
	return (0);
}

int			mouse_release(int button, int x, int y, t_fdf *node)
{
	if (button == 1)
	{
		node->mouse_x = x;
		node->mouse_y = y;
		node->mouse_1 = 0;
	}
	if (button == 2)
	{
		node->mouse_x = x;
		node->mouse_y = y;
		node->mouse_2 = 0;
	}
	return (0);
}

int			mouse_press(int button, int x, int y, t_fdf *node)
{
	if (button == 1)
	{
		node->mouse_x = x;
		node->mouse_y = y;
		node->mouse_1 = 1;
	}
	if (button == 2)
	{
		node->mouse_x = x;
		node->mouse_y = y;
		node->mouse_2 = 1;
	}
	return (0);
}
