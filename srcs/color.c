/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:55 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/25 17:40:58 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			if (map->points[y][x].coordinates[Z] == map->z_min)
				map->points[y][x].color = FULL_BLUE;
			if (map->points[y][x].coordinates[Z] == 0)
				map->points[y][x].color = FULL_GREEN;
		}
	}
}