/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:38:19 by joao              #+#    #+#             */
/*   Updated: 2024/02/19 03:19:26 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../complete_lib/mlx_linux/mlx.h"
# include "../complete_lib/libft/libft.h"
# include "../complete_lib/ft_printf/ft_printf.h"
# include "../complete_lib/get_next_line/get_next_line_bonus.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

# define HEX "0123456789ABCDEF"

# define WIDTH 1920
# define HEIGHT 1080

# define MENU_WIDTH 350

# define MOUSE_L_CLICK 1
# define MOUSE_M_CLICK 2
# define MOUSE_R_CLICK 3
# define MOUSE_W_UP 4
# define MOUSE_W_DOWN 5

# define ZERO 48
# define ONE 49
# define TWO 50
# define THREE 51
# define FOUR 52
# define FIVE 53
# define SIX 54
# define SEVEN 55
# define EIGHT 56
# define NINE 57
# define KA 97
# define KB 98
# define KC 99
# define KD 100
# define KE 101
# define KF 102
# define KG 103
# define KH 104
# define KI 105
# define KJ 106
# define KK 107
# define KL 108
# define KM 109
# define KN 110
# define KO 111
# define KP 112
# define KQ 113
# define KR 114
# define KS 115
# define KT 116
# define KU 117
# define KV 118
# define KW 119
# define KX 120
# define KY 121
# define KZ 122
# define L_ARROW 65361
# define D_ARROW 65364
# define R_ARROW 65363
# define U_ARROW 65362
# define PLUS 61
# define MINUS 45
# define L_SHIFT 65505
# define L_CTRL 65507
# define L_ALT 65513
# define ESC 65307

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
# define BLUEISH_TONES 2
# define SOFTER_TONES 3
# define BRIGHT_TONES 4
# define HIGH_CONTRAST 5
# define ANOTHER_EARTH 6
# define BRIGHT_PASTEL 7
# define PINKISH_PASTEL 8

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

# define MENU_BACKGROUND 0xFF151515
# define BUTTON 0xFFAAAAAA
# define BUTTON_STR 0xFF000000
# define NBR_YELLOW 0xFFE1E100
# define SELECTION 0xFFCC00CC

# define START_PAR 30
# define END_PAR 60
# define INITIAL_MERIDIAN -100
# define ORIGIN_LAT 40

# define INFO "<================MAP INFORMATION================>"
# define INFO_SIZE "Number of Points: "
# define INFO_X_Y "X Limit:        Y Limit: "
# define INFO_X "X Limit: "
# define INFO_ZMAX_ZMIN "Minimum Z:        Maximum Z: "
# define INFO_ZMIN "Minimum Z: "

# define DETAILS "<=================FRAME DETAILS=================>"
# define ANGLES "Angles in use for rotation"
# define SPACES "X[    ] Y[    ] Z[    ]"
# define X_SPACE "X["
# define Y_SPACE "X[    ] Y["
# define Z_SPACE "X[    ] Y[    ] Z["
# define ZOOM "Zoom multiplier: "
# define X_MUL "X multiplier: "
# define Y_MUL "Y multiplier: "
# define Z_MUL "Z multiplier: "
# define STR_TRANSLATION_VEL "Translation velocity: "
# define STR_ROTATION_VEL "Rotation velocity: "
# define STR_SCALE_VEL "Scale velocity: "

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
# define TRANSLATION "Mouse Lclick -> Translation"
# define ARROWS "Arrow keys -> Translation"
# define RMOUSE_ROT "Left Shift + Mouse Rclick -> Z Axis Rotation"
# define LMOUSE_ROT "Left Shift + Mouse Lclick -> X and Y Axis Rotation"
# define X_ROT "Q/E -> X Axis Rotation"
# define Y_ROT "A/D -> Y Axis Rotation"
# define Z_ROT "W/S -> Z Axis Rotation"
# define ZOOM_CHANGE "N/M -> Zoom out/in"
# define MOUSE_W "Mouse Wheel -> Zoom out/in"
# define S_MOUSE_W "Left Shift + Mouse Wheel -> Change X Multiplier"
# define C_MOUSE_W "Left CTRL + Mouse Wheel -> Change Y Multiplier"
# define A_MOUSE_W "Left ALT + Mouse Wheel -> Change Z Multiplier"
# define PROJ_CHANGE "O/P -> Projection Change"
# define SCHEME_CHANGE "H -> Color Scheme Change"
# define ROT_VEL "-/+ -> Rotation Velocity"
# define TRANSLATION_VEL "Left Shift + -/+ -> Translation Velocity"
# define SCALE_VEL "Left CTRL + -/+ -> Scale Velocity"
# define MAP_CHANGE "L -> Map Change"
# define INVERT "I -> Invert Colors"

# define MAP_NAME "<===================CURRENT MAP=================>"

# define Y_START 30
# define X_START 30

typedef struct s_lambert
{
	float	start_parallel;
	float	end_parallel;
	float	meridian;
	float	origin_lat;
	float	major_axis;
	float	parallel_median;
	float	radial_distance;
	float	theta_long;
	float	theta_lat;
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
	int	mouse_r;
	int	shift;
	int	ctrl;
	int	alt;
}				t_pressed;

typedef struct s_colors
{
	int	t_color;
	int	t_t_color;
	int	m_color;
	int	b_t_color;
	int	b_color;
}				t_colors;

typedef struct s_map
{
	int			z_max;
	int			z_min;
	int			z_range;
	int			z_pos_range;
	int			z_neg_range;
	float		t_vel;
	float		r_vel;
	float		s_vel;
	int			proj;
	char		**map_info;
	int			den;
	float		scale;
	float		f_scale;
	float		mul[3];
	int			lim[2];
	float		angles[3];
	float		radius;
	int			spherical;
	int			conic;
	int			scheme;
	int			inverted;
	char		*name;
	t_colors	color_scheme;
	t_pressed	b_pressed;
	t_point		origin;
	t_point		**points;
	t_lambert	l_vars;
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
	int			in_use;
	t_map		*map;
	int			menu;
}				t_vars;

char	**read_map(t_map *map, char *file);
t_point	**copy_map(t_map original_map);
void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color);
void	vars_init(t_vars *fdf, char *title);
void	map_init(t_map *map, char *name);
int		parser(t_map *map, char *file);
void	draw_map(t_vars *fdf);
t_point	matmul(float mat[3][3], t_point point);
void	rotatex(t_map *map, t_point **proj, int angle);
void	rotatey(t_map *map, t_point **proj, int angle);
void	rotatez(t_map *map, t_point **proj, int angle);
void	orthographic(t_map *map, t_point **proj);
void	change_projection(int keycode, t_vars *fdf);
int		end_program(t_vars *fdf, int maps, int no_vars);
void	isometric(t_vars *fdf);
void	top_view(t_vars *fdf);
void	choose_projection(t_vars *fdf, int prespective);
void	keys_translation(int keycode, t_vars *fdf);
int		key_press(int keycode, t_vars *fdf);
int		key_release(int keycode, t_vars *fdf);
void	change_scale(int keycode, t_vars *fdf);
void	change_z_mul(int keycode, t_vars *fdf);
int		mouse_press(int button, int x, int y, t_vars *fdf);
int		map_movement(int x, int y, t_vars *fdf);
int		render_frame(t_vars *fdf);
void	translations(t_vars *fdf);
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
char	*ft_ftoa(float n, int precision);
t_map	*input_info_init(t_vars *fdf, int argc);
void	choose_color_scheme(t_map *map);
int		mouse_release(int button, int x, int y, t_vars *fdf);
void	invert_color(t_point *point);
void	turn_negative(t_vars *fdf);
void	menu_button(t_vars *fdf);
long	ft_strhextol(char *str);
void	behind_menu(t_point *pixel);
int		update_color_gradient(int startcolor, int endcolor,
			float len, float pixels);
void	dda(t_vars *fdf, t_point start, t_point end);
void	change_color_scheme(t_vars *fdf, int keycode);
void	keys_rotation(int keycode, t_vars *fdf);
void	change_mov_vel(int keycode, t_vars *fdf);
void	change_rot_vel(int keycode, t_vars *fdf);
void	reset_position(t_vars *fdf);
void	change_map(t_vars *fdf);
void	rotations(t_vars *fdf);
void	keys_rotation(int keycode, t_vars *fdf);
void	translations(t_vars *fdf);
void	keys_translation(int keycode, t_vars *fdf);
int		ft_round(float n);
int		get_x_y_limits(t_map *map, char *file);
void	find_best_z_mul(t_map *map);
void	change_scale_vel(int keycode, t_vars *fdf);
void	put_info(t_vars *fdf, int *y);
void	put_angles(t_vars *fdf, int *y);
void	put_zoom(t_vars *fdf, int *y);
void	put_velocities(t_vars *fdf, int *y);
void	put_scheme(t_vars *fdf, int *y);
void	put_proj(t_vars *fdf, int *y);
void	put_controls(t_vars *fdf, int *y);
void	put_in_use_name(t_vars *fdf, int *y);
void	choose_str_color(t_vars *fdf, int y, char *str, int flag);
int		next_line(int *y);
int		x_end(char *str);
t_point	**get_proj(t_map original_map);

#endif