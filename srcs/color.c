/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:55 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/08 16:22:27 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	update_color_gradient(int startcolor, int endcolor, int len, int pixels)
{
	float	color_increment[4];
	int		updated_color[4];

	color_increment[T] = ((endcolor >> 24 & 0xFF) - (startcolor >> 24 & 0xFF)) / len;
	color_increment[R] = ((endcolor >> 16 & 0xFF) - (startcolor >> 16 & 0xFF)) / len;
	color_increment[G] = ((endcolor >> 8 & 0xFF) - (startcolor >> 8 & 0xFF)) / len;
	color_increment[B] = ((endcolor & 0xFF) - (startcolor & 0xFF)) / len;
	updated_color[T] = (startcolor >> 24 & 0xFF) + round(pixels * color_increment[T]);
	updated_color[R] = (startcolor >> 16 & 0xFF) + round(pixels * color_increment[R]);
	updated_color[G] = (startcolor >> 8 & 0xFF) + round(pixels * color_increment[G]);
	updated_color[B] = (startcolor & 0xFF) + round(pixels * color_increment[B]);
	return((updated_color[T] << 24) + (updated_color[R] << 16) + (updated_color[G] << 8) + updated_color[B]);
}

void	set_point_color(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			if (map->points[y][x].coordinates[Z] == map->z_max)
				map->points[y][x].color = WHITE;
			else if (map->points[y][x].coordinates[Z] == map->z_min && map->points[y][x].coordinates[Z] != 0)
				map->points[y][x].color = FULL_BLUE;
			else if (map->points[y][x].coordinates[Z] == 0)
				map->points[y][x].color = FULL_GREEN;
			else if (map->points[y][x].coordinates[Z] > 0)
				map->points[y][x].color = update_color_gradient(WHITE, FULL_GREEN, map->z_max, map->z_max - map->points[y][x].coordinates[Z]);
			else
				map->points[y][x].color = update_color_gradient(FULL_BLUE, FULL_GREEN, -map->z_min, -(map->z_min - map->points[y][x].coordinates[Z]));
		}
	}
}