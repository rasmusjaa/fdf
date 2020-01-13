/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:29:17 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/13 12:11:25 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

static void	make_projection(t_fdf *node)
{
	if (node->projection == 2)
	{
		parallel_top(&node->x1, &node->y1, &node->z1, node);
		parallel_top(&node->x2, &node->y2, &node->z2, node);
		center_top(node);
	}
	else
	{
		isometric(&node->x1, &node->y1, &node->z1, node);
		isometric(&node->x2, &node->y2, &node->z2, node);
		center_iso(node);
	}
}

static void	image_set(int x, int y, t_fdf *node)
{
	if (x >= 0 && y >= 0 && x < WINDOW_X && y < WINDOW_Y)
		*(int*)(node->data_addr + (((y * WINDOW_X) + x)
		* node->bpp)) = node->color;
}

/*
**	Instead of our own image_set we could use mlx_pixel_put, but it's slow
**	 mlx_pixel_put(node->mlx_ptr, node->win_ptr,
**		node->x1, node->y1, node->color);
*/

static int	out_of_bounds(float x1, float x2, float y1, float y2)
{
	if (x1 < 0 && x2 < 0)
		return (1);
	if (y1 < 0 && y2 < 0)
		return (1);
	if (x1 > WINDOW_X && x2 > WINDOW_X)
		return (1);
	if (y1 > WINDOW_Y && y2 > WINDOW_Y)
		return (1);
	return (0);
}

void		bresenham_x(float x1, float y1, t_fdf *node)
{
	float		x_plus;
	float		y_plus;
	int			big;

	node->x1 = x1;
	node->y1 = y1;
	node->x2 = x1 + 1;
	node->y2 = y1;
	node->z1 = node->grid[(int)node->y1][(int)node->x1] * node->z;
	node->z2 = node->grid[(int)node->y2][(int)node->x2] * node->z;
	zoom_and_color(node);
	make_projection(node);
	x_plus = node->x2 - node->x1;
	y_plus = node->y2 - node->y1;
	big = (abs_nb(x_plus) >= abs_nb(y_plus) ? abs_nb(x_plus) : abs_nb(y_plus));
	x_plus /= big;
	y_plus /= big;
	if (out_of_bounds(node->x1, node->x2, node->y1, node->y2) == 1)
		return ;
	while ((int)(node->x2 - node->x1) || (int)(node->y2 - node->y1))
	{
		image_set(node->x1, node->y1, node);
		node->x1 += x_plus;
		node->y1 += y_plus;
	}
}

void		bresenham_y(float x1, float y1, t_fdf *node)
{
	float		x_plus;
	float		y_plus;
	int			big;

	node->x1 = x1;
	node->y1 = y1;
	node->x2 = x1;
	node->y2 = y1 + 1;
	node->z1 = node->grid[(int)node->y1][(int)node->x1] * node->z;
	node->z2 = node->grid[(int)node->y2][(int)node->x2] * node->z;
	zoom_and_color(node);
	make_projection(node);
	x_plus = node->x2 - node->x1;
	y_plus = node->y2 - node->y1;
	big = (abs_nb(x_plus) >= abs_nb(y_plus) ? abs_nb(x_plus) : abs_nb(y_plus));
	x_plus /= big;
	y_plus /= big;
	if (out_of_bounds(node->x1, node->x2, node->y1, node->y2))
		return ;
	while ((int)(node->x2 - node->x1) || (int)(node->y2 - node->y1))
	{
		image_set(node->x1, node->y1, node);
		node->x1 += x_plus;
		node->y1 += y_plus;
	}
}
