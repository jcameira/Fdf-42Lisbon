/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:32 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/24 18:49:30 by jcameira         ###   ########.fr       */
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
	map->projection = 0;
	map->scale = 75;
	map->z_multiplier = 10;
	map->angles[X] = 30;
	map->angles[Y] = 330;
	map->angles[Z] = 45;
	map->origin.coordinates[X] = WIDTH / 2;
	map->origin.coordinates[Y] = HEIGHT / 2;
	map->origin.coordinates[Z] = 0;
}
