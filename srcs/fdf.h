/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:38:19 by joao              #+#    #+#             */
/*   Updated: 2024/02/09 00:07:05 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../complete_lib/mlx_linux/mlx.h"
# include "../complete_lib/libft/libft.h"
# include "../complete_lib/get_next_line/get_next_line_bonus.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

# define WIDTH 1920
# define HEIGHT 1080

# define X 0
# define Y 1
# define Z 2

# define T 0
# define R 1
# define G 2
# define B 3

# define LONGITUDE 0
# define LATITUDE 1

# define ISOMETRIC 0

# define WHITE 0xFFFFFFFF
# define FULL_BLUE 0xFF0000FF
# define FULL_GREEN 0xFF00FF00

typedef struct s_point
{
	int		color;
	float	coordinates[3];
	float	polar[2];
}				t_point;

typedef struct s_pressed
{
	int	close;
	int	pos_rot_x;
	int	neg_rot_x;
	int	pos_rot_y;
	int	neg_rot_y;
	int	pos_rot_z;
	int	neg_rot_z;
	int	mov_l;
	int	mov_r;
	int	mov_u;
	int	mov_d;
}				t_pressed;

typedef struct s_map
{
	int			z_max;
	int			z_min;
	int			z_range;
	int			translation_velocity;
	int			rotation_velocity;
	int			projection;
	char		**map_info;
	float		scale;
	int			point_density;
	float		z_multiplier;
	float		limits[2];
	float		angles[3];
	float		radius;
	int			spherical;
	t_pressed	b_pressed;
	t_point		origin;
	t_point		**points;
}				t_map;

typedef struct s_bitmap
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_bitmap;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_bitmap	bitmap;
	t_map		map;
}				t_vars;

char	**read_map(t_map *map, char *file);
void	copy_map(t_point ***projection, t_map original_map);
void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color);
void	vars_init(t_vars *fdf, char *title);
void	map_init(t_map *map);
void	parser(t_map *map, char *file);
void	draw_map(t_vars *fdf);
t_point	matmul(float mat[3][3], t_point point);
void	rotatex(t_map *map, t_point **projection, int angle);
void	rotatey(t_map *map, t_point **projection, int angle);
void	rotatez(t_map *map, t_point **projection, int angle);
void	orthographic(t_map *map, t_point **projection);
void	change_prespective(int keycode, t_vars *fdf);
void	end_program(t_vars *fdf);
void	isometric(t_vars *fdf);
void	top_view(t_vars *fdf);
void	choose_prespective(t_vars *fdf, int prespective);
void	keys_origin(int keycode, t_vars *fdf);
int		key_press(int keycode, t_vars *fdf);
int		key_release(int keycode, t_vars *fdf);
void	change_scale(int keycode, t_vars *fdf);
void	change_z_multiplier(int keycode, t_vars *fdf);
int		mouse_press(int button, int x, int y, t_vars *fdf);
int		map_translation(int x, int y, t_vars *fdf);
int		render_frame(t_vars *fdf);
void	move_origin(t_vars *fdf);
void	set_point_color(t_map *map);
void	update_z_limits(t_map *map, t_point **points);
int		update_color_gradient(int start, int end, int len, int pixels);
int		inside_window(t_vars *fdf, t_point point);
void	free_projection(t_point **projection, t_map map);
void	fit_window(t_vars *fdf);

#endif