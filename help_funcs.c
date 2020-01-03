/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:28:30 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/02 14:49:45 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
// yhdista
#include "fdf.h"

long long	abs_nb(long long x)
{
	if (x < 0)
		return (-1 * x);
		else
	return (x);
}

float	abs_f(float x)
{
	if (x < 0)
		return (-1 * x);
		else
	return (x);
}

void		zoom(float *x1, float *x2, float *y1, float *y2, t_fdf *node)
{
	*x1 *= node->zoom;
	*x2 *= node->zoom;
	*y1 *= node->zoom;
	*y2 *= node->zoom;
}
