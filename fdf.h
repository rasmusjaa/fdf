/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:45:14 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/01/03 13:17:01 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define WINDOW_X 1200
# define WINDOW_Y 1000
# define WHITE 0xffffff

typedef struct		s_fdf
{
	int		width;
	int		height;
	char	**strings;
	int		**grid;
	void	*mlx_ptr;
	void	*win_ptr;
	float	zoom;
	int		color;
	float	move_x;
	float	move_y;
	float	z;
	float	z1;
	float	z2;
	int		max_z;
	int		min_z;
	int		iso_y;
	int		iso_x;
	int		iso_z;
	int		projection;
}					t_fdf;

int			get_grid(char *str,  t_fdf *node);

int			get_map(char *str, t_fdf *node);
void		map_to_window(t_fdf *node);

void		bresenham_x(float x1, float y1, t_fdf *node);
void		bresenham_y(float x1, float y1, t_fdf *node);

void		center_iso(float *x1, float *x2, float *y1, float *y2, t_fdf *node);
void		isometric(float *x, float *y, float *z, t_fdf *node);
void		center_top(float *x1, float *x2, float *y1, float *y2, t_fdf *node);
void		parallel_top(float *x, float *y, float *z, t_fdf *node);

long long	abs_nb(long long x);
float		abs_f(float x);
void		zoom(float *x1, float *x2, float *y1, float *y2, t_fdf *node);
