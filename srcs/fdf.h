/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:38:19 by joao              #+#    #+#             */
/*   Updated: 2024/01/22 20:54:52 by jcameira         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080

# define X 0
# define Y 1
# define Z 2

# define ISOMETRIC 0

typedef struct s_point
{
	int		color;
	float	coordinates[3];
}				t_point;

typedef struct s_map
{
	int		z_max;
	int		z_min;
	int		z_range;
	int		projection;
	char	**map_info;
	float	scale;
	float	limits[3];
	float	angles[3];
	t_point	*origin;
	t_point **points;
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
	t_bitmap	*bitmap;
	t_map		*map;
}				t_vars;

char	**read_map(t_map *map, char *file);
void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color);
t_vars	*vars_init(char *title);
t_map   *map_init(void);
t_map	*parser(char *file);
void    draw_map(t_vars *fdf);
t_point matmul(float mat[3][3], t_point point);
void    rotatex(t_map *map, int angle);
void    rotatey(t_map *map, int angle);
void    rotatez(t_map *map, int angle);
void    orthographic(t_map *map);
int		show_keycode(int keycode, t_vars *fdf);
int 	change_prespective(int keycode, t_vars *fdf);
int 	end_program(int keycode, t_vars *fdf);
void    isometric(t_vars *fdf);
void    top_view(t_vars *fdf);
void    choose_prespective(t_vars *fdf, int  prespective);

#endif