/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:45:14 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/13 11:59:24 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WINDOW_X 1200
# define WINDOW_Y 1000
# define MAX_HEIGHT 500
# define MAX_WIDTH 500
# define MAX_Z 500
# define WHITE 0xffffff

typedef struct		s_fdf
{
	int		width;
	int		height;
	char	**strings;
	int		**grid;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	float	zoom;
	int		color;
	float	move_x;
	float	move_y;
	float	z;
	float	z1;
	float	z2;
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	max_z;
	float	min_z;
	int		rot_y;
	int		rot_x;
	int		rot_z;
	int		projection;
	int		mouse_1;
	int		mouse_2;
	int		mouse_x;
	int		mouse_y;
}					t_fdf;

typedef	struct		s_fdf_list
{
	char				*content;
	struct s_fdf_list	*next;
}					t_fdf_list;

void				color_z(t_fdf *node);

int					deal_key(int key, t_fdf *node);

void				bresenham_x(float x1, float y1, t_fdf *node);
void				bresenham_y(float x1, float y1, t_fdf *node);

int					close_exit(t_fdf *node);
int					exit_message(char *message);
void				check_max_z(t_fdf *node);
long long			abs_nb(long long x);
float				abs_f(float x);

void				map_to_window(t_fdf *node);

int					mouse_move(int x, int y, t_fdf *node);
int					mouse_release(int button, int x, int y, t_fdf *node);
int					mouse_press(int button, int x, int y, t_fdf *node);

int					get_map(char *str, t_fdf *node);

void				zoom_and_color(t_fdf *node);
void				center_iso(t_fdf *node);
void				isometric(float *x, float *y, float *z, t_fdf *node);
void				center_top(t_fdf *node);
void				parallel_top(float *x, float *y, float *z, t_fdf *node);

#endif
