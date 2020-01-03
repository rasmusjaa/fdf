/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:24:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/03 13:12:05 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ft_printf.h"
// yhdista
#include "fdf.h"

void		center_iso(float *x1, float *x2, float *y1, float *y2, t_fdf *node)
{
	*x1 += (WINDOW_X / 2 + (node->zoom * node->width / 8)) + node->move_x;
	*x2 += (WINDOW_X / 2 + (node->zoom * node->width / 8)) + node->move_x;
	*y1 += (WINDOW_Y / 2 - (node->zoom * node->height / 2)) + node->move_y;
	*y2 += (WINDOW_Y / 2 - (node->zoom * node->height / 2)) + node->move_y;
}

void		isometric(float *x, float *y, float *z, t_fdf *node)
{
	float	tempx;
	float	tempy;

	tempx = *x;
	*x = (*x - *y) *  cos(30 * (M_PI / 180.0f));
	*y = (tempx + *y) * sin(30 * (M_PI / 180.0f));
	*y -= *z;
	// rotate x
	tempy = *y;
	*y = *y * cos(node->iso_x * M_PI / 180.0f) + *z * sin(node->iso_x * M_PI / 180.0f);
	*z = -1 * tempy * sin(node->iso_x * M_PI / 180.0f) + *z * cos(node->iso_x * M_PI / 180.0f);
	// rotate y
	tempx = *x;
	*x = *x * cos(node->iso_y * M_PI / 180.0f) + *z * sin(node->iso_y * M_PI / 180.0f);
	*z = -1 * tempx * sin(node->iso_y * M_PI / 180.0f) + *z * cos(node->iso_y * M_PI / 180.0f);
	// rotate z
	tempx = *x;
	*x = *x * cos(node->iso_z * M_PI / 180.0f) - *y * sin(node->iso_z * M_PI / 180.0f);
	*y = tempx * sin(node->iso_z * M_PI / 180.0f) + *y * cos(node->iso_z * M_PI / 180.0f);
}

void		center_top(float *x1, float *x2, float *y1, float *y2, t_fdf *node)
{
	*x1 += (WINDOW_X / 2 - (node->zoom * node->width / 2)) + node->move_x;
	*x2 += (WINDOW_X / 2 - (node->zoom * node->width / 2)) + node->move_x;
	*y1 += (WINDOW_Y / 2 - (node->zoom * node->height / 2)) + node->move_y;
	*y2 += (WINDOW_Y / 2 - (node->zoom * node->height / 2)) + node->move_y;
}

void		parallel_top(float *x, float *y, float *z, t_fdf *node)
{
	float	tempx;
	float	tempy;

	tempx = *x;
	// rotate x
	tempy = *y;
	*y = *y * cos(node->iso_x * M_PI / 180.0f) + *z * sin(node->iso_x * M_PI / 180.0f);
	*z = -1 * tempy * sin(node->iso_x * M_PI / 180.0f) + *z * cos(node->iso_x * M_PI / 180.0f);
	// rotate y
	tempx = *x;
	*x = *x * cos(node->iso_y * M_PI / 180.0f) + *z * sin(node->iso_y * M_PI / 180.0f);
	*z = -1 * tempx * sin(node->iso_y * M_PI / 180.0f) + *z * cos(node->iso_y * M_PI / 180.0f);
	// rotate z
	tempx = *x;
	*x = *x * cos(node->iso_z * M_PI / 180.0f) - *y * sin(node->iso_z * M_PI / 180.0f);
	*y = tempx * sin(node->iso_z * M_PI / 180.0f) + *y * cos(node->iso_z * M_PI / 180.0f);

}
