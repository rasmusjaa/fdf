/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:05:00 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/08 19:12:02 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	color_pos(float z, t_fdf *node)
{
	float	z_range;

	z_range = node->max_z * node->zoom * node->z / 15;
	if (z / z_range > 0.8)
		node->color = 0x0023BF;
	else if (z / z_range > 0.6)
		node->color = 0x006EC2;
	else if (z / z_range > 0.4)
		node->color = 0x00BCC6;
	else if (z / z_range > 0.2)
		node->color = 0x00CA87;
	else
		node->color = 0x00CE3B;
}

static void	color_neg(float z, t_fdf *node)
{
	float	z_range;

	z_range = node->max_z * node->zoom * node->z / 15;
	if (z / z_range > 0.8)
		node->color = 0xE50000;
	else if (z / z_range > 0.6)
		node->color = 0xE15500;
	else if (z / z_range > 0.4)
		node->color = 0xDDA800;
	else if (z / z_range > 0.2)
		node->color = 0xBAD900;
	else
		node->color = 0x65D500;
}

void		color_z(t_fdf *node)
{
	float	z;

	z = (node->z1 + node->z2) / 2;
	node->color = 0x13D200;
	if ((int)z > 0)
	{
		color_pos(z, node);
	}
	if ((int)z < 0)
		color_neg(z, node);
}
