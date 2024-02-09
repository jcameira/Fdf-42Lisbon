/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:32 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/08 23:59:22 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vars_init(t_vars *fdf, char *title)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, title);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
}

void	map_init(t_map *map)
{
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->projection = 0;
	map->scale = 1;
	map->point_density = 8 / map->scale;
	map->z_multiplier = 1;
	map->translation_velocity = 10;
	map->rotation_velocity = 1;
	map->angles[X] = 30;
	map->angles[Y] = 330;
	map->angles[Z] = 45;
	map->origin.coordinates[X] = WIDTH / 2;
	map->origin.coordinates[Y] = HEIGHT / 2;
	map->origin.coordinates[Z] = 0;
	map->spherical = 0;
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
