/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:00:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/08 19:21:14 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"

static void	node_values(t_fdf *node)
{
	node->zoom = node->width >= node->height ? WINDOW_X /
		(node->width * 2) : WINDOW_X / (node->height * 2);
	if (node->zoom > 100)
		node->zoom = 100;
	node->color = WHITE;
	node->move_x = 0;
	node->move_y = 0;
	node->z = 1;
	node->rot_x = 0;
	node->rot_y = 0;
	node->rot_z = 0;
	node->projection = 1;
}

int			main(int ac, char **av)
{
	t_fdf	*node;

	if (!(node = (t_fdf *)malloc(sizeof(t_fdf))))
		return (1);
	if (ac != 2)
		exit_message("Give 1 map file as argument");
	node->max_z = -1 * MAX_Z;
	node->min_z = MAX_Z;
	if (get_map(av[1], node) != 0)
		return (1);
	node->mlx_ptr = mlx_init();
	node->win_ptr = mlx_new_window(node->mlx_ptr, WINDOW_X, WINDOW_Y, "FDF");
	node_values(node);
	node->img_ptr = mlx_new_image(node->mlx_ptr, WINDOW_X, WINDOW_Y);
	node->data_addr = mlx_get_data_addr(node->img_ptr,
		&node->bpp, &node->size_line, &node->endian);
	node->bpp /= 8;
	map_to_window(node);
	mlx_hook(node->win_ptr, 2, 0, deal_key, node);
	mlx_hook(node->win_ptr, 17, 0, close_exit, node);
	mlx_loop(node->mlx_ptr);
	return (0);
}
