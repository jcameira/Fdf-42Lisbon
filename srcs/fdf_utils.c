/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:39:58 by joao              #+#    #+#             */
/*   Updated: 2024/02/09 01:42:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//void	fit_window(t_vars *fdf)
//{
//	
//}

int	inside_window(t_vars *fdf, t_point point)
{
	if (fdf->map.origin.coordinates[X] + point.coordinates[X] >= 0
		&& fdf->map.origin.coordinates[X] + point.coordinates[X] <= WIDTH)
		if (fdf->map.origin.coordinates[Y] + point.coordinates[Y] >= 0
			&& fdf->map.origin.coordinates[Y] + point.coordinates[Y] <= HEIGHT)
			return (1);
	return (0);
}

void	copy_map(t_point ***projection, t_map original_map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < original_map.limits[Y])
	{
		x = -1;
		while (++x < original_map.limits[X])
		{
			(*projection)[y][x] = original_map.points[y][x];
			(*projection)[y][x].coordinates[X] *= original_map.scale;
			(*projection)[y][x].coordinates[Y] *= original_map.scale;
			(*projection)[y][x].coordinates[Z] *= original_map.z_multiplier;
			(*projection)[y][x].color = original_map.points[y][x].color;
		}
	}
	update_z_limits(&original_map, *projection);
}

void	faster_pixel_put(t_bitmap *bitmap, int x, int y, int color)
{
	char	*offset;

	offset = bitmap->address + (y * bitmap->line_length
			+ x * (bitmap->bits_per_pixel / 8));
	*(unsigned int *)offset = color;
}
