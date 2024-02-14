/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:39:58 by joao              #+#    #+#             */
/*   Updated: 2024/02/14 12:52:33 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_scale_dependants(t_map *map, float increment, int reset)
{
	map->point_density = 8 / map->scale;
	if (map->point_density == 0)
		map->point_density = 1;
	map->radius = (map->limits[X] * map->scale) / (M_PI * 2);
	map->lambert_vars.major_axis = map->scale
		* ((float)map->limits[X] / (float)20);
	if (reset)
	{
		map->x_multiplier = 1;
		map->y_multiplier = 1;
		map->z_multiplier = 1;
	}
	map->x_multiplier += increment;
	if (map->x_multiplier < 1)
		map->x_multiplier = 1;
	map->y_multiplier += increment;
	if (map->y_multiplier < 1)
		map->y_multiplier = 1;
	map->z_multiplier += increment;
	if (map->z_multiplier < 1)
		map->z_multiplier = 1;
}

void	fit_window(t_vars *fdf)
{
	t_point	**proj;
	int		x;
	int		y;

	proj = copy_map(fdf->map[fdf->current_map]);
	while (1)
	{
		y = -1;
		while (++y < fdf->map[fdf->current_map].limits[Y])
		{
			x = -1;
			while (++x < fdf->map[fdf->current_map].limits[X])
			{
				if (!inside_window(fdf, proj[y][x]))
				{
					free_proj(proj, fdf->map[fdf->current_map]);
					return ;
				}
			}
		}
		fdf->map[fdf->current_map].scale += 0.1;
		update_scale_dependants(&fdf->map[fdf->current_map], 0.1, 0);
		free_proj(proj, fdf->map[fdf->current_map]);
		proj = copy_map(fdf->map[fdf->current_map]);
	}
}

int	inside_window(t_vars *fdf, t_point point)
{
	if (fdf->map[fdf->current_map].origin.coord[X] + point.coord[X] >= 0
		&& fdf->map[fdf->current_map].origin.coord[X] + point.coord[X] <= WIDTH)
		if (fdf->map[fdf->current_map].origin.coord[Y] + point.coord[Y] >= 0
			&& fdf->map[fdf->current_map].origin.coord[Y] + point.coord[Y] <= HEIGHT)
			return (1);
	return (0);
}

t_point	**copy_map(t_map original_map)
{
	t_point	**proj;
	int		x;
	int		y;

	proj = malloc(sizeof (t_point *) * original_map.limits[Y]);
	y = -1;
	while (++y < original_map.limits[Y])
		proj[y] = malloc(sizeof (t_point) * original_map.limits[X]);
	y = -1;
	while (++y < original_map.limits[Y])
	{
		x = -1;
		while (++x < original_map.limits[X])
		{
			proj[y][x] = original_map.points[y][x];
			proj[y][x].coord[X] *= original_map.x_multiplier;
			proj[y][x].coord[Y] *= original_map.y_multiplier;
			proj[y][x].coord[Z] *= original_map.z_multiplier;
			proj[y][x].color = original_map.points[y][x].color;
			proj[y][x].paint = 1;
		}
	}
	update_z_limits(&original_map, proj);
	return (proj);
}

void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color)
{
	char	*offset;

	offset = bitmap->address + (y * bitmap->line_length
			+ x * (bitmap->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}
