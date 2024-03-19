/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:32 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/19 17:23:46 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_map	*input_info_init(t_vars *fdf, int argc)
{
	t_map	*map;

	map = malloc(sizeof (t_map) * (argc - 1));
	if (!map)
		return (NULL);
	fdf->number_of_maps = argc - 1;
	fdf->in_use = 0;
	return (map);
}

void	vars_init(t_vars *fdf, char *title)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, title);
	fdf->bitmap.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap.address = mlx_get_data_addr(fdf->bitmap.img,
			&fdf->bitmap.bits_per_pixel, &fdf->bitmap.line_length,
			&fdf->bitmap.endian);
	fdf->menu = 1;
}

void	lambert_init(t_map *map)
{
	map->l_vars.start_parallel = START_PAR;
	map->l_vars.end_parallel = END_PAR;
	map->l_vars.meridian = INITIAL_MERIDIAN;
	map->l_vars.origin_lat = ORIGIN_LAT;
	map->l_vars.major_axis = map->scale * ((float)map->lim[X] / (float)20);
	map->l_vars.parallel_median = (sin(map->l_vars.start_parallel)
			+ sin(map->l_vars.end_parallel)) / 2;
	map->l_vars.radial_distance = pow(cos(map->l_vars.start_parallel), 2)
		+ 2 * map->l_vars.parallel_median * sin(map->l_vars.start_parallel);
}

void	buttons_init(t_map *map)
{
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
	map->b_pressed.shift = 0;
	map->b_pressed.ctrl = 0;
	map->b_pressed.alt = 0;
	map->b_pressed.mouse_l = 0;
	map->b_pressed.mouse_r = 0;
}

void	map_init(t_map *map, char *name)
{
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->proj = 0;
	map->scale = 1;
	map->den = 8 / map->scale;
	map->lim[Y] = 0;
	map->mul[X] = 1;
	map->mul[Y] = 1;
	map->mul[Z] = 1;
	map->t_vel = 1;
	map->r_vel = 1;
	map->s_vel = 0.1;
	map->angles[X] = 30;
	map->angles[Y] = 330;
	map->angles[Z] = 45;
	map->origin.coord[X] = WIDTH / 2;
	map->origin.coord[Y] = HEIGHT / 2;
	map->origin.coord[Z] = 0;
	map->spherical = 0;
	map->conic = 0;
	map->scheme = 0;
	map->inverted = 0;
	map->name = name;
	lambert_init(map);
	buttons_init(map);
}
