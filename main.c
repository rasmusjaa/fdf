/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:00:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/03 12:05:29 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
// yhdista
#include "fdf.h"

int 		deal_key(int key, t_fdf *node)
{
	if (key == 53) // esc
	{
		mlx_destroy_window(node->mlx_ptr, node->win_ptr);
		exit(0);
	}
	else if (key == 18) // 1
	{
		node->projection = 1;
		node->iso_x = 0;
		node->iso_y = 0;
		node->iso_z = 0;
	}
	else if (key == 19) // 2
	{
		node->projection = 2;
		node->iso_x = 0;
		node->iso_y = 0;
		node->iso_z = 0;
	}
	else if (key == 123) // left
		node->move_x -= 20;
	else if (key == 124) // right
		node->move_x += 20;
	else if (key == 125) // down
		node->move_y += 20;
	else if (key == 126) // up
		node->move_y -= 20;
	else if (key == 78) // -
	{
		(node->z /= 2);
		(node->zoom /= 2);
	}
	else if (key == 69) // +
	{
		(node->z *= 2);
		(node->zoom *= 2);
	}
	else if (key == 75) // /
	{
		node->z -= 1;
	}
	else if (key == 67) // *
	{
		node->z += 1;
	}
	else if (key == 91) // num up 8
		(node->iso_x += 10);
	else if (key == 84) // num down 2
		(node->iso_x -= 10);
	else if (key == 86) // num left 4
		(node->iso_y += 10);
	else if (key == 88) // num right 6
		(node->iso_y -= 10);
	else if (key == 83) // num 1
		(node->iso_z += 10);
	else if (key == 92) // num 9
		(node->iso_z -= 10);
	mlx_clear_window(node->mlx_ptr, node->win_ptr);
	map_to_window(node);
	return(0);
}

void		node_values(t_fdf *node)
{
	node->zoom = node->width >= node->height ? WINDOW_X /
		(node->width * 2) : WINDOW_X / (node->height * 2);
	node->color = WHITE;
	node->move_x = 0;
	node->move_y = 0;
	node->z = 1;
	node->iso_x = 0;
	node->iso_y = 0;
	node->iso_z = 0;
	node->projection = 1;
}

int			main(int ac, char **av)
{
	t_fdf	*node;

	if (!(node = (t_fdf *)malloc(sizeof(t_fdf))))
		return (1);
	if (ac != 2)
	{
		ft_printf("Give 1 map file as argument\n");
		return (0);
	}
	node->max_z = 0;
	node->min_z = 0;
	if (get_map(av[1], node) != 0)
		return (-1);
	node->mlx_ptr = mlx_init();
	node->win_ptr = mlx_new_window(node->mlx_ptr, WINDOW_X, WINDOW_Y, "FDF");
	node_values(node);
	map_to_window(node);

/*
**  return void *0 if failed
*/

	mlx_key_hook(node->win_ptr, deal_key, node);
/*
	img_ptr = mlx_new_image(mlx_ptr, 20, 20);
	mlx_get_data_addr(img_ptr,   int   *bits_per_pixel,  int *size_line, int *endian );
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 20, 20);
*/
	mlx_loop(node->mlx_ptr);
	return (0);
}

/*
int	mlx_loop ( void *mlx_ptr ); // always needed
int	mlx_key_hook ( void *win_ptr, int (*funct_ptr)(), void *param );
int	mlx_mouse_hook ( void *win_ptr, int (*funct_ptr)(), void *param );
int	mlx_expose_hook ( void *win_ptr, int (*funct_ptr)(), void *param );
int	mlx_loop_hook ( void *mlx_ptr, int (*funct_ptr)(), void *param );
*/

/*
void *mlx_new_window ( void *mlx_ptr, int size_x, int size_y, char *title );
int	mlx_clear_window ( void *mlx_ptr, void *win_ptr );
int	mlx_destroy_window ( void *mlx_ptr, void *win_ptr );
*/

/*
void *mlx_new_image ( void *mlx_ptr, int width, int height );
char *mlx_get_data_addr   (   void   *img_ptr,   int   *bits_per_pixel,  int *size_line, int *endian );
int mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );
unsigned int mlx_get_color_value ( void *mlx_ptr, int color );
void *mlx_xpm_to_image  (  void  *mlx_ptr,  char **xpm_data, int *width, int *height );
void *mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height );
int mlx_destroy_image ( void *mlx_ptr, void *img_ptr );
*/

/*
int mlx_pixel_put  ( void *mlx_ptr, void *win_ptr, int x, int y, int color);
**  color is 0xAARRGGBB format
int mlx_string_put ( void *mlx_ptr, void  *win_ptr,  int  x,  int  y,  int color, char *string );
*/
