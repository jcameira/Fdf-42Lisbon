/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:38:19 by joao              #+#    #+#             */
/*   Updated: 2024/01/05 20:31:24 by joao             ###   ########.fr       */
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
	float	scale;
	float	limits[3];
	float	angles[3];
	t_point	*origin;
	t_point **points;
}

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

#endif