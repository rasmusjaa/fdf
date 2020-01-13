/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:30:21 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/09 14:51:17 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

/*
** numpad 8 2 4 6 1 9: xyz rotations
*/

static void	deal_key3(int key, t_fdf *node)
{
	if (key == 91)
		(node->rot_x += 10);
	else if (key == 84)
		(node->rot_x -= 10);
	else if (key == 86)
		(node->rot_y += 10);
	else if (key == 88)
		(node->rot_y -= 10);
	else if (key == 83)
		(node->rot_z += 10);
	else if (key == 92)
		(node->rot_z -= 10);
}

/*
** arrow left right down up: movement, - and +: zoom, / and *: multiply z
*/

static void	deal_key2(int key, t_fdf *node)
{
	if (key == 123)
		node->move_x -= 20;
	else if (key == 124)
		node->move_x += 20;
	else if (key == 125)
		node->move_y += 20;
	else if (key == 126)
		node->move_y -= 20;
	else if (key == 78 && node->zoom > 2)
		node->zoom /= 2;
	else if (key == 69 && node->zoom < 100)
		node->zoom *= 2;
	else if (key == 75 && node->z > -5 && node->max_z * node->z > -1 * MAX_Z / 2
			&& node->min_z * node->z < MAX_Z / 2)
		node->z -= 1;
	else if (key == 67 && node->z < 5 && node->max_z * node->z < MAX_Z / 2
			&& node->min_z * node->z > -1 * MAX_Z / 2)
		node->z += 1;
}

/*
** esc: exit, 1 and 2: projections
*/

static void	deal_key1(int key, t_fdf *node)
{
	if (key == 53)
	{
		mlx_destroy_image(node->mlx_ptr, node->img_ptr);
		mlx_destroy_window(node->mlx_ptr, node->win_ptr);
		close_exit(node);
	}
	else if (key == 18)
	{
		node->projection = 1;
		node->rot_x = 0;
		node->rot_y = 0;
		node->rot_z = 0;
		node->move_x = 0;
		node->move_y = 0;
	}
	else if (key == 19)
	{
		node->projection = 2;
		node->rot_x = 0;
		node->rot_y = 0;
		node->rot_z = 0;
		node->move_x = 0;
		node->move_y = 0;
	}
}

int			deal_key(int key, t_fdf *node)
{
	deal_key1(key, node);
	deal_key2(key, node);
	deal_key3(key, node);
	mlx_destroy_image(node->mlx_ptr, node->img_ptr);
	node->img_ptr = mlx_new_image(node->mlx_ptr, WINDOW_X, WINDOW_Y);
	mlx_clear_window(node->mlx_ptr, node->win_ptr);
	map_to_window(node);
	return (0);
}
