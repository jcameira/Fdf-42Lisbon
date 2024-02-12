/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:38:19 by joao              #+#    #+#             */
/*   Updated: 2024/02/12 18:45:31 by jcameira         ###   ########.fr       */
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
# define TOP_VIEW 1
# define SIDE_VIEW 2
# define FRONT_VIEW 3
# define CONIC 4
# define SPHERE 5

# define DEFAULT 0
# define EARTH 1
# define MONO_W 2
# define GROOVY 3

# define WHITE 0xFFFFFFFF
# define FULL_BLUE 0xFF0000FF
# define FULL_GREEN 0xFF00FF00
# define NBR_YELLOW 0xFFE1E100
# define SELECTION 0xFFCC00CC

# define MLX fdf->mlx
# define WIN fdf->win

# define INFO "MAP INFORMATION"
# define INFO_SIZE "Number of Points: "
# define SIZE fdf->map.limits[X] * fdf->map.limits[Y]
# define INFO_X "X Limit: "
# define X_LIM fdf->map.limits[X]
# define INFO_Y "Y Limit: "
# define Y_LIM fdf->map.limits[Y]
# define INFO_ZMAX "Maximum Z: "
# define ZMAX fdf->map.z_max
# define INFO_ZMIN "Minimum Z: "
# define ZMIN fdf->map.z_min

# define DETAILS "FRAME DETAILS"
# define ANGLES "Angles in use for rotation"
# define SPACES "X[    ] Y[    ] Z[    ]"
# define X_ANGLE fdf->map.angles[X]
# define Y_ANGLE fdf->map.angles[Y]
# define Z_ANGLE fdf->map.angles[Z]
# define ZOOM "Zoom multiplier: "
# define SCALE fdf->map.scale
# define Z_MUL "Z multiplier: "
# define Z_VAL_MUL fdf->map.z_multiplier

# define SCHEME "COLOR SCHEMES"
# define STR_DEFAULT "1: Default"
# define STR_EARTH "2: Earth"
# define STR_MONO_W "3: Monochromatic White"
# define NEG_ON "Negative Mode: ON"
# define NEG_OFF "Negative Mode: OFF"

# define VIEW "PROJECTION TYPES"
# define STR_ISOMETRIC "Isometric Projection"
# define STR_TOP_VIEW "Top View Projection"
# define STR_SIDE_VIEW "Side View Projection"
# define STR_FRONT_VIEW "Front View Projection"
# define STR_CONIC "Conic Projection"
# define STR_SPHERE "Spheric Projection" 

# define CONTROLS "CONTROLS"

# define Y_START 30
# define X_START 30
# define NEXT_LINE(current_y) (current_y = 30 * (__COUNTER__) + Y_START, current_y - 1)
# define X_END(str) (X_START + ft_strlen(str) * 6)
# define X_SPACE (X_START + ft_strlen("X[") * 6)
# define Y_SPACE (X_START + ft_strlen("X[    ] Y[") * 6)
# define Z_SPACE (X_START + ft_strlen("X[    ] Y[    ] Z[") * 6)
# define TO_STR(int) ft_itoa(int)

typedef struct s_point
{
	int		color;
	int		paint;
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
	int			limits[2];
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
t_point	**copy_map(t_map original_map);
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
void	free_map(t_map *map);
void	free_split(char **split);
void	update_scale_dependants(t_map *map);
void	draw_menu(t_vars *fdf);
void	menu_background(t_vars *fdf);
void	behind_menu(t_point *pixel);
void	put_info(t_vars *fdf);

#endif