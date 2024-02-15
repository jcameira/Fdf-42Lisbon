/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:38:19 by joao              #+#    #+#             */
/*   Updated: 2024/02/15 16:45:50 by jcameira         ###   ########.fr       */
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

# define MENU_WIDTH 350

# define X 0
# define Y 1
# define Z 2

# define T 0
# define R 1
# define G 2
# define B 3

# define LONGITUDE 0
# define LATITUDE 1

# define DEFAULT 0
# define EARTH 1
# define BLUEISH_TONES 2
# define SOFTER_TONES 3
# define BRIGHT_TONES 4
# define HIGH_CONTRAST 5
# define ANOTHER_EARTH 6
# define BRIGHT_PASTEL 7
# define PINKISH_PASTEL 8

# define ISOMETRIC 0
# define TOP_VIEW 1
# define SIDE_VIEW 2
# define FRONT_VIEW 3
# define CONIC 4
# define SPHERE 5

# define WHITE 0xFFFFFFFF
# define SOFT_ORANGE 0xFFFF9933
# define GROUND_GREEN 0xFF4C9900
# define DARKISH_AQUA 0xFF00CCCC
# define FULL_BLUE 0xFF0000FF

# define ALMOST_WHITE 0xFFEFF6E0
# define GREENISH_GREY 0xFFAEC3B0
# define GREYISH_BLUE 0xFF598392
# define DEEP_OCEAN 0xFF124559
# define ALMOST_BLACK 0xFF01161E

# define EGGSHELL 0xFFF7E1D7
# define SOFT_PINK 0xFFEDAFB8
# define BLUEISH_GREY 0xFFDEDBD2
# define GREYISH_GREEN 0xFFB0C4B1
# define DARK_GREY 0xFF4A5759

# define WHITE 0xFFFFFFFF
# define ORANGE 0xFFEF8354
# define GREY 0xFFBFC0C0
# define GREY_BLUE 0xFF4F5D75
# define REDISH_GREY 0xFF2D3142

# define WHITE 0xFFFFFFFF
# define BRIGHT_ORANGE 0xFFFF9F1C
# define BRIGHT_RED 0xFFE71D36
# define BRIGHT_AQUA 0xFF2EC4B6
# define VERY_DARK_BLUE 0xFF011627

# define ANOTHER_EGGSHELL 0xFFFFECD1
# define BRIGHTER_ORANGE 0xFFFF7D00
# define BROWN 0xFF78290F
# define GREENISH_BLUE 0xFF15616D
# define MORE_DARK_BLUE 0xFF001524

# define PASTEL_ORANGE 0xFFF4A261
# define PASTEL_YELLOW 0xFFE9C46A
# define PASTEL_SALMON 0xFFE78F51
# define PASTEL_AQUA 0xFF2A9D8F
# define PASTEL_OCEAN 0xFF264653

# define SOFT_SALMON 0xFFEAAC8B
# define PINKISH 0xFFE56B6F
# define PINKISH_WINE 0xFFB56576
# define DARK_PURPLE 0xFF6D597A
# define MORE_GREYISH_BLUE 0xFF355070

# define NBR_YELLOW 0xFFE1E100
# define SELECTION 0xFFCC00CC

# define START_PAR 30
# define END_PAR 60
# define INITIAL_MERIDIAN -100
# define ORIGIN_LAT 40

# define MLX fdf->mlx
# define WIN fdf->win

# define INFO "<================MAP INFORMATION================>"
# define INFO_SIZE "Number of Points: "
# define SIZE fdf->map[fdf->current_map].limits[X] * fdf->map[fdf->current_map].limits[Y]
# define INFO_X_Y "X Limit:        Y Limit: "
# define INFO_X "X Limit: "
# define X_LIM fdf->map[fdf->current_map].limits[X]
# define INFO_Y "Y Limit: "
# define Y_LIM fdf->map[fdf->current_map].limits[Y]
# define INFO_ZMAX_ZMIN "Maximum Z:        Minimum Z: "
# define INFO_ZMAX "Maximum Z: "
# define ZMAX fdf->map[fdf->current_map].z_max
# define INFO_ZMIN "Minimum Z: "
# define ZMIN fdf->map[fdf->current_map].z_min

# define DETAILS "<=================FRAME DETAILS=================>"
# define ANGLES "Angles in use for rotation"
# define SPACES "X[    ] Y[    ] Z[    ]"
# define X_ANGLE fdf->map[fdf->current_map].angles[X]
# define Y_ANGLE fdf->map[fdf->current_map].angles[Y]
# define Z_ANGLE fdf->map[fdf->current_map].angles[Z]
# define ZOOM "Zoom multiplier: "
# define SCALE fdf->map[fdf->current_map].scale
# define Z_MUL "Z multiplier: "
# define Z_VAL_MUL fdf->map[fdf->current_map].z_multiplier

# define SCHEME "<=================COLOR SCHEMES=================>"
# define STR_DEFAULT "1: Default"
# define STR_EARTH "2: Earth"
# define STR_BLUEISH_TONES "3: Blueish Tones"
# define STR_SOFTER_TONES "4: Softer Tones"
# define STR_BRIGHT_TONES "5: Brighter Tones"
# define STR_HIGH_CONTRAST "6: High Contrast"
# define STR_ANOTHER_EARTH "7: Another Earth"
# define STR_BRIGHT_PASTEL "8: Bright Pastel"
# define STR_PINKISH_PASTEL "9: Pinkish Pastel"
# define NEG_ON "Negative Mode: ON"
# define NEG_OFF "Negative Mode: OFF"

# define VIEW "<================Projection TYPE================>"
# define STR_ISOMETRIC "Isometric Projection"
# define STR_TOP_VIEW "Top View Projection"
# define STR_SIDE_VIEW "Side View Projection"
# define STR_FRONT_VIEW "Front View Projection"
# define STR_CONIC "Conic Projection"
# define STR_SPHERE "Spheric Projection" 

# define CONTROLS "<====================CONTROLS===================>"
# define X_ROT "Q/E -> X Axis Rotation"
# define Y_ROT "A/D -> Y Axis Rotation"
# define Z_ROT "W/S -> Z Axis Rotation"
# define TRANSLATION "Mouse Lclick drag -> Translation"
# define ZOOM_CHANGE "N/M -> Zoom out/in"
# define PROJ_CHANGE "P -> Projection Change"
# define SCHEME_CHANGE "H -> Color Scheme Change"
# define ROT_VEL "-/+ -> Rotation Velocity"
# define TRANSLATION_VEL "{/} -> Translation Velocity"
# define MAP_CHANGE "L -> Map Change"
# define INVERT "U -> Invert Colors"

# define Y_START 30
# define X_START 30
# define NEXT_LINE(current_y) (current_y = 20 * (__COUNTER__) + Y_START, current_y - 1)
# define X_END(str) (X_START + ft_strlen(str) * 6)
# define X_SPACE (X_START + ft_strlen("X[") * 6)
# define Y_SPACE (X_START + ft_strlen("X[    ] Y[") * 6)
# define Z_SPACE (X_START + ft_strlen("X[    ] Y[    ] Z[") * 6)
# define TO_STR(int) ft_itoa(int)
# define FTO_STR(int) ftoa(int, 1)
# define PARALLEL_MEDIAN (sin(vars->start_parallel) + sin(vars->end_parallel)) / 2
# define RADIAL_DISTANCE pow(cos(vars->start_parallel), 2) + 2 * vars->parallel_median * sin(vars->start_parallel)
# define THETA_LONG map->lambert_vars.parallel_median * (proj[y][x].polar[LONGITUDE] - map->lambert_vars.meridian)
# define THETA_LAT map->lambert_vars.parallel_median * (proj[y][x].polar[LATITUDE] - map->lambert_vars.origin_lat)
# define RHO map->lambert_vars.major_axis * sqrt(map->lambert_vars.radial_distance) / map->lambert_vars.parallel_median * tan(M_PI / 4 - THETA_LAT / 2)

typedef struct s_lambert
{
	float	start_parallel;
	float	end_parallel;
	float	meridian;
	float	origin_lat;
	float	major_axis;
	float	parallel_median;
	float	radial_distance;
}				t_lambert;

typedef struct s_point
{
	int		original_color;
	int		color;
	int		paint;
	float	coord[3];
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
	int	mouse_l;
	int mouse_r;
	int	shift;
}				t_pressed;

typedef struct s_colors
{
	int	top_color;
	int	top_transition_color;
	int	mid_color;
	int	bottom_transition_color;
	int	bottom_color;
}				t_colors;

typedef struct s_map
{
	int			z_max;
	int			z_min;
	int			z_range;
	int			z_pos_range;
	int			z_neg_range;
	int			translation_velocity;
	int			rotation_velocity;
	int			proj;
	char		**map_info;
	int			point_density;
	float		scale;
	float		x_multiplier;
	float		y_multiplier;
	float		z_multiplier;
	int			limits[2];
	float		angles[3];
	float		radius;
	int			spherical;
	int			conic;
	int			scheme;
	int			inverted;
	t_colors	color_scheme;
	t_pressed	b_pressed;
	t_point		origin;
	t_point		**points;
	t_lambert	lambert_vars;
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
	int			number_of_maps;
	int			current_map;
	t_map		*map;
}				t_vars;

char	**read_map(t_map *map, char *file);
t_point	**copy_map(t_map original_map);
void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color);
void	vars_init(t_vars *fdf, char *title);
void	map_init(t_map *map);
void	parser(t_map *map, char *file);
void	draw_map(t_vars *fdf);
t_point	matmul(float mat[3][3], t_point point);
void	rotatex(t_map *map, t_point **proj, int angle);
void	rotatey(t_map *map, t_point **proj, int angle);
void	rotatez(t_map *map, t_point **proj, int angle);
void	orthographic(t_map *map, t_point **proj);
void	change_prespective(int keycode, t_vars *fdf);
int		end_program(t_vars *fdf);
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
int		update_color_gradient(int start, int end, float len, float pixels);
int		inside_window(t_vars *fdf, t_point point);
void	free_proj(t_point **proj, t_map map);
void	fit_window(t_vars *fdf);
void	free_map(t_map *map);
void	free_split(char **split);
void	update_scale_dependants(t_map *map, float increment, int reset);
void	draw_menu(t_vars *fdf);
void	menu_background(t_vars *fdf);
void	behind_menu(t_point *pixel);
void	put_info(t_vars *fdf);
char	*ftoa(float n, int precision);
t_map	*input_info_init(t_vars *fdf, int argc);
void	choose_color_scheme(t_map *map);
int		mouse_release(int button, int x, int y, t_vars *fdf);
void	invert_color(t_point *point);
void	turn_negative(t_vars *fdf);

#endif