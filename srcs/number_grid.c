/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:08:11 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/08 19:53:37 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include "fdf.h"

static int			line_to_grid(char *line, t_fdf *node, int current)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_strsplit(line, ' ');
	while (array[i])
		i++;
	if (!(node->grid[current] = (int *)malloc(sizeof(int) * i)))
		return (0);
	i = 0;
	while (array[i])
	{
		node->grid[current][i] = ft_atoi(array[i]);
		if ((float)node->grid[current][i] > node->max_z)
			node->max_z = (float)node->grid[current][i];
		if ((float)node->grid[current][i] < node->min_z)
			node->min_z = (float)node->grid[current][i];
		free(array[i]);
		i++;
	}
	free(array);
	check_max_z(node);
	return (i);
}

static int			make_grid(t_fdf_list *start, t_fdf *node)
{
	t_fdf_list	*tmp;
	int			i;
	int			compare;

	if (!(node->grid = (int **)malloc(sizeof(int *) * node->height)))
		return (1);
	i = 0;
	compare = -1;
	while (start->content)
	{
		tmp = start;
		node->width = line_to_grid(start->content, node, i);
		if (compare == -1)
			compare = node->width;
		if (compare != node->width || compare == 0)
			exit_message("Lines not valid, exiting");
		free(start->content);
		start = start->next;
		free(tmp);
		i++;
	}
	free(start);
	return (0);
}

static t_fdf_list	*fdf_list_add(char *line)
{
	t_fdf_list	*list;

	if (!(list = (t_fdf_list *)malloc(sizeof(t_fdf_list))))
		return (NULL);
	if (!line)
		list->content = NULL;
	else
		list->content = line;
	list->next = NULL;
	return (list);
}

static t_fdf_list	*map_list(char *str, t_fdf *node)
{
	int			fd;
	char		*line;
	int			i;
	t_fdf_list	*start;
	t_fdf_list	*elem;

	if (!(start = fdf_list_add(NULL)))
		return (NULL);
	elem = start;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		elem->content = line;
		if (!(elem->next = fdf_list_add(NULL)))
			return (NULL);
		elem = elem->next;
		i++;
	}
	node->height = i;
	close(fd);
	return (start);
}

int					get_map(char *str, t_fdf *node)
{
	t_fdf_list	*start;

	start = map_list(str, node);
	if (!start)
		return (1);
	if (node->height > MAX_HEIGHT)
	{
		ft_printf("Map y %d exceeds set max (%d)", node->height, MAX_HEIGHT);
		exit(0);
	}
	ft_printf("Map height %d\n", node->height);
	if (make_grid(start, node) != 0)
		return (1);
	if (node->height > MAX_HEIGHT)
	{
		ft_printf("Map x %d exceeds set max (%d)", node->width, MAX_WIDTH);
		exit(0);
	}
	ft_printf("Map width %d\n", node->width);
	if (node->height < 1 || node->width < 1
			|| (node->height == 1 && node->width == 1))
		return (-1);
	ft_printf("Z values: max %.f & min %.f\n", node->max_z, node->min_z);
	return (0);
}
