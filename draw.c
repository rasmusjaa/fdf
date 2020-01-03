/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:29:17 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/03 13:22:43 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
// yhdista
#include "fdf.h"

static void	color_pos(float z, t_fdf *node)
{
	if (z / (node->max_z * node->z) > 0.8)
		node->color = 0x0023BF;
	else if (z / (node->max_z * node->z) > 0.6)
		node->color = 0x006EC2;
	else if (z / (node->max_z * node->z) > 0.4)
		node->color = 0x00BCC6;
	else if (z / (node->max_z * node->z) > 0.2)
		node->color = 0x00CA87;
	else
		node->color = 0x00CE3B;
}

static void	color_neg(float z, t_fdf *node)
{
	if (abs_f(-1 * z / (node->max_z * node->z)) > 0.8)
		node->color = 0xE50000;
	else if (abs_f(-1 * z / (node->max_z * node->z)) > 0.6)
		node->color = 0xE15500;
	else if (abs_f(-1 * z / (node->max_z * node->z)) > 0.4)
		node->color = 0xDDA800;
	else if (abs_f(-1 * z / (node->max_z * node->z)) > 0.2)
		node->color = 0xBAD900;
	else
		node->color = 0x65D500;
}

static void	color_z(float z1, float z2, t_fdf *node)
{
	int		diff;
	float	z;

	diff = node->max_z - node->min_z;
	z = (z1 + z2) / 2;
	node->color = 0x13D200;
	if ((int)z > 0)
		color_pos(z, node);
	if ((int)z < 0)
		color_neg(z, node);
}

static void	draw_projection(float *x1, float *x2, float *y1, float *y2, t_fdf *node)
{
	if (node->projection == 2)
	{
		parallel_top(x1, y1, &node->z1, node);
		parallel_top(x2, y2, &node->z2, node);
		center_top(x1, x2, y1, y2, node);
	}
	else
	{
		isometric(x1, y1, &node->z1, node);
		isometric(x2, y2, &node->z2, node);
		center_iso(x1, x2, y1, y2, node);
	}
}

void		bresenham_x(float x1, float y1, t_fdf *node)
{
	float		x_plus;
	float		y_plus;
	int			bigger;
	float		x2;
	float		y2;

	x2 = x1 + 1;
	y2 = y1;
	node->z1 = node->grid[(int)y1][(int)x1] * node->z;
	node->z2 = node->grid[(int)y2][(int)x2] * node->z;
	zoom(&x1, &x2, &y1, &y2, node);
	color_z(node->z1, node->z2, node);
	draw_projection(&x1, &x2, &y1, &y2, node);
	x_plus = x2 - x1;
	y_plus = y2 - y1;
	bigger = (abs_nb(x_plus) >= abs_nb(y_plus) ? abs_nb(x_plus) : abs_nb(y_plus));
	x_plus /= bigger;
	y_plus /= bigger;
	while ((int)(x2 - x1) || (int)(y2 - y1))
	{
		mlx_pixel_put(node->mlx_ptr, node->win_ptr, x1, y1, node->color);
		x1 += x_plus;
		y1 += y_plus;
	}
}

void		bresenham_y(float x1, float y1, t_fdf *node)
{
	float		x_plus;
	float		y_plus;
	int			bigger;
	float		x2;
	float		y2;

	x2 = x1;
	y2 = y1 + 1;
	node->z1 = node->grid[(int)y1][(int)x1] * node->z;
	node->z2 = node->grid[(int)y2][(int)x2] * node->z;
	zoom(&x1, &x2, &y1, &y2, node);
	color_z(node->z1, node->z2, node);
	draw_projection(&x1, &x2, &y1, &y2, node);
	x_plus = x2 - x1;
	y_plus = y2 - y1;
	bigger = (abs_nb(x_plus) >= abs_nb(y_plus) ? abs_nb(x_plus) : abs_nb(y_plus));
	x_plus /= bigger;
	y_plus /= bigger;
	while ((int)(x2 - x1) || (int)(y2 - y1))
	{
		mlx_pixel_put(node->mlx_ptr, node->win_ptr, x1, y1, node->color);
		x1 += x_plus;
		y1 += y_plus;
	}
}
