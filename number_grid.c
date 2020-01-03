/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:08:11 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/02 15:47:40 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
// yhdista
#include "fdf.h"

int			init_grid(t_fdf *node)
{
	int		i;

	if (!(node->grid = (int **)malloc(sizeof(int *) * node->height)))
		return (1);
	i = 0;
	while (i < node->height)
	{
		if (!(node->grid[i] = (int *)malloc(sizeof(int) * node->width)))
			return (1);
		i++;
	}
	return (0);
}

int			line_to_grid(char *line, t_fdf *node, int current)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_strsplit(line, ' ');
	while (array[i])
	{
		node->grid[current][i] = ft_atoi(array[i]);
		if (node->grid[current][i] > node->max_z)
			node->max_z = node->grid[current][i];
		if (node->grid[current][i] < node->min_z)
			node->min_z = node->grid[current][i];
		free (array[i]);
		i++;
	}
	free (array);
	if (i != node->width)
	{
		ft_printf("Line widths aren't equal\n");
		return (1);
	}
	return (0);
}

int			get_grid(char *str,  t_fdf *node)
{
	int		fd;
	char	*line;
	int		i;

	if (init_grid(node) != 0)
		return (1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	while (i < node->height)
	{
		ft_get_next_line(fd, &line);
		if (line_to_grid(line, node, i) != 0)
			return (1);
		free(line);
		i++;
	}
	if (i != node->height)
		return (1);
	close(fd);
	return (0);
}
