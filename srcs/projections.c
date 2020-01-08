/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:24:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/08 19:19:53 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void		zoom_and_color(t_fdf *node)
{
	node->x1 *= node->zoom;
	node->x2 *= node->zoom;
	node->y1 *= node->zoom;
	node->y2 *= node->zoom;
	node->z1 *= node->zoom / 15;
	node->z2 *= node->zoom / 15;
	color_z(node);
}

void		center_iso(t_fdf *node)
{
	node->x1 += (WINDOW_X / 2) + node->move_x;
	node->x2 += (WINDOW_X / 2) + node->move_x;
	node->y1 += (WINDOW_Y / 2 - (node->zoom * node->height / 2));
	node->y2 += (WINDOW_Y / 2 - (node->zoom * node->height / 2));
	node->y1 += node->move_y + ((node->min_z + node->max_z)
		/ 2 * (node->zoom / 15));
	node->y2 += node->move_y + ((node->min_z + node->max_z)
		/ 2 * (node->zoom / 15));
}

/*
** First isometric coordinate setting, then XYZ rotations
*/

void		isometric(float *x, float *y, float *z, t_fdf *node)
{
	float	tempx;
	float	tempy;

	tempx = *x;
	*x = (*x - *y) * cos(30 * (M_PI / 180.0f));
	*y = (tempx + *y) * sin(30 * (M_PI / 180.0f));
	*y -= *z;
	tempy = *y;
	*y = *y * cos(node->rot_x * M_PI / 180.0f) +
		*z * sin(node->rot_x * M_PI / 180.0f);
	*z = -1 * tempy * sin(node->rot_x * M_PI / 180.0f) +
		*z * cos(node->rot_x * M_PI / 180.0f);
	*x = *x * cos(node->rot_y * M_PI / 180.0f) +
		*z * sin(node->rot_y * M_PI / 180.0f);
	*z = -1 * tempx * sin(node->rot_y * M_PI / 180.0f) +
		*z * cos(node->rot_y * M_PI / 180.0f);
	*x = *x * cos(node->rot_z * M_PI / 180.0f) -
		*y * sin(node->rot_z * M_PI / 180.0f);
	*y = tempx * sin(node->rot_z * M_PI / 180.0f) +
		*y * cos(node->rot_z * M_PI / 180.0f);
}

void		center_top(t_fdf *node)
{
	node->x1 += (WINDOW_X / 2 - (node->zoom * node->width / 2)) + node->move_x;
	node->x2 += (WINDOW_X / 2 - (node->zoom * node->width / 2)) + node->move_x;
	node->y1 += (WINDOW_Y / 2 - (node->zoom * node->height / 2)) + node->move_y;
	node->y2 += (WINDOW_Y / 2 - (node->zoom * node->height / 2)) + node->move_y;
}

/*
** Same as isometric but no initial coordinate setting, just XYZ rotations
*/

void		parallel_top(float *x, float *y, float *z, t_fdf *node)
{
	float	tempx;
	float	tempy;

	tempx = *x;
	tempy = *y;
	*y = *y * cos(node->rot_x * M_PI / 180.0f) +
		*z * sin(node->rot_x * M_PI / 180.0f);
	*z = -1 * tempy * sin(node->rot_x * M_PI / 180.0f) +
		*z * cos(node->rot_x * M_PI / 180.0f);
	*x = *x * cos(node->rot_y * M_PI / 180.0f) +
		*z * sin(node->rot_y * M_PI / 180.0f);
	*z = -1 * tempx * sin(node->rot_y * M_PI / 180.0f) +
		*z * cos(node->rot_y * M_PI / 180.0f);
	*x = *x * cos(node->rot_z * M_PI / 180.0f) -
		*y * sin(node->rot_z * M_PI / 180.0f);
	*y = tempx * sin(node->rot_z * M_PI / 180.0f) +
		*y * cos(node->rot_z * M_PI / 180.0f);
}
