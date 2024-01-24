/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:39:58 by joao              #+#    #+#             */
/*   Updated: 2024/01/24 12:30:46 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_map(t_point **projection, t_map original_map)
{
	int	x;
	int	y;

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
		}
	}
}

void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color)
{
	char	*offset;

	offset = bitmap->address + (y * bitmap->line_length
			+ x * (bitmap->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}
