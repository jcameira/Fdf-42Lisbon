/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:39:58 by joao              #+#    #+#             */
/*   Updated: 2024/02/10 16:36:24 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_scale_dependants(t_map *map)
{
	map->point_density = 8 / map->scale;
	if (map->point_density == 0)
		map->point_density = 1;
	map->radius = (map->limits[X] * map->scale) / (M_PI * 2);
}

void	fit_window(t_vars *fdf)
{
	t_point **projection;
	int		x;
	int		y;

	projection = copy_map(fdf->map);
	while (1)
	{
		y = -1;
		while (++y < fdf->map.limits[Y])
		{
			x = -1;
			while (++x < fdf->map.limits[X])
			{
				if (!inside_window(fdf, projection[y][x]))
				{
					free_projection(projection, fdf->map);
					return ;
				}
			}
		}
		fdf->map.scale += 0.1;
		update_scale_dependants(&fdf->map);
		free_projection(projection, fdf->map);
		projection = copy_map(fdf->map);
	}
}

int	inside_window(t_vars *fdf, t_point point)
{
	if (fdf->map.origin.coordinates[X] + point.coordinates[X] >= 0
		&& fdf->map.origin.coordinates[X] + point.coordinates[X] <= WIDTH)
		if (fdf->map.origin.coordinates[Y] + point.coordinates[Y] >= 0
			&& fdf->map.origin.coordinates[Y] + point.coordinates[Y] <= HEIGHT)
			return (1);
	return (0);
}

t_point	**copy_map(t_map original_map)
{
	t_point **projection;
	int	x;
	int	y;

	projection = malloc(sizeof (t_point *) * original_map.limits[Y]);
	y = -1;
	while (++y < original_map.limits[Y])
		projection[y] = malloc(sizeof (t_point) * original_map.limits[X]);
	y = -1;
	while (++y < original_map.limits[Y])
	{
		x = -1;
		while (++x < original_map.limits[X])
		{
			projection[y][x] = original_map.points[y][x];
			projection[y][x].coordinates[X] *= original_map.scale;
			projection[y][x].coordinates[Y] *= original_map.scale;
			projection[y][x].coordinates[Z] *= original_map.z_multiplier;
			projection[y][x].color = original_map.points[y][x].color;
			projection[y][x].paint = 1;
		}
	}
	update_z_limits(&original_map, projection);
	return(projection);
}

void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color)
{
	char	*offset;

	offset = bitmap->address + (y * bitmap->line_length
			+ x * (bitmap->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}
