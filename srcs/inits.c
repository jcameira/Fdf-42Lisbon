/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:32 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/15 01:22:21 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*input_info_init(t_vars *fdf, int argc)
{
	t_map *map;

	map = malloc(sizeof (t_map) * (argc - 1));
	fdf->number_of_maps = argc - 1;
	fdf->current_map = 0;
	return(map);
}

void	vars_init(t_vars *fdf, char *title)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, title);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
}

void	lambert_init(t_lambert *vars, t_map *map)
{
	vars->start_parallel = START_PAR;
	vars->end_parallel = END_PAR;
	vars->meridian = INITIAL_MERIDIAN;
	vars->origin_lat = ORIGIN_LAT;
	vars->major_axis = map->scale * ((float)map->limits[X] / (float)20);
	vars->parallel_median = PARALLEL_MEDIAN;
	vars->radial_distance = RADIAL_DISTANCE;
}

void	map_init(t_map *map)
{
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->proj = 0;
	map->scale = 1;
	map->point_density = 8 / map->scale;
	map->x_multiplier = 1;
	map->y_multiplier = 1;
	map->z_multiplier = 1;
	map->translation_velocity = 10;
	map->rotation_velocity = 1;
	map->angles[X] = 30;
	map->angles[Y] = 330;
	map->angles[Z] = 45;
	map->origin.coord[X] = WIDTH / 2;
	map->origin.coord[Y] = HEIGHT / 2;
	map->origin.coord[Z] = 0;
	map->spherical = 0;
	map->conic = 0;
	map->scheme = 0;
	lambert_init(&map->lambert_vars, map);
	map->b_pressed.mov_d = 0;
	map->b_pressed.mov_u = 0;
	map->b_pressed.mov_l = 0;
	map->b_pressed.mov_r = 0;
	map->b_pressed.pos_rot_x = 0;
	map->b_pressed.neg_rot_x = 0;
	map->b_pressed.pos_rot_y = 0;
	map->b_pressed.neg_rot_y = 0;
	map->b_pressed.pos_rot_z = 0;
	map->b_pressed.neg_rot_z = 0;
}
