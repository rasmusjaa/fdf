/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:28:30 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/08 19:54:14 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "fdf.h"

int			close_exit(t_fdf *node)
{
	int		i;

	i = 0;
	while (i < node->height)
	{
		free(node->grid[i]);
		i++;
	}
	free(node->grid);
	free(node);
	exit(0);
}

int			exit_message(char *message)
{
	ft_printf("%s\n", message);
	exit(0);
}

void		check_max_z(t_fdf *node)
{
	if ((int)node->max_z > MAX_Z || abs((int)node->min_z) > MAX_Z)
	{
		ft_printf("Exceeded set max z value (%d), exiting\n", MAX_Z);
		exit(0);
	}
}

long long	abs_nb(long long x)
{
	if (x < 0)
		return (-1 * x);
	else
		return (x);
}

float		abs_f(float x)
{
	if (x < 0)
		return (-1 * x);
	else
		return (x);
}
