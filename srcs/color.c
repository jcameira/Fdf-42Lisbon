/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:55 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/29 13:26:23 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_point_color(t_map *map, t_point **points)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			if (points[y][x].coordinates[Z] == map->z_max)
				points[y][x].color = WHITE;
			if (points[y][x].coordinates[Z] == map->z_min)
				points[y][x].color = FULL_BLUE;
			if (points[y][x].coordinates[Z] == 0)
				points[y][x].color = FULL_GREEN;
		}
	}
}