/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/08 13:45:23 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	spherize(t_map *map, t_point **projection)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			projection[y][x].coordinates[X] = (map->radius + projection[y][x].coordinates[Z]) * \
			sin(projection[y][x].polar[LATITUDE]) * cos(projection[y][x].polar[LONGITUDE]);
			projection[y][x].coordinates[Y] = (map->radius + projection[y][x].coordinates[Z]) * \
			sin(projection[y][x].polar[LATITUDE]) * sin(projection[y][x].polar[LONGITUDE]);
			projection[y][x].coordinates[Z] = (map->radius + projection[y][x].coordinates[Z]) * \
			cos(projection[y][x].polar[LATITUDE]);
		}
	}
}

void	connect_points(t_vars *fdf, t_point start, t_point end)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	delta.coordinates[X] = (fdf->map.origin.coordinates[X] + end.coordinates[X]) - (fdf->map.origin.coordinates[X] + start.coordinates[X]);
	delta.coordinates[Y] = (fdf->map.origin.coordinates[Y] + end.coordinates[Y]) - (fdf->map.origin.coordinates[Y] + start.coordinates[Y]);
	pixels = sqrt((delta.coordinates[X] * delta.coordinates[X]) + \
			(delta.coordinates[Y] * delta.coordinates[Y]));
	printf("Pixels: %d\n", pixels);
	len = pixels;
	delta.coordinates[X] /= pixels;
	delta.coordinates[Y] /= pixels;
	pixel.coordinates[X] = fdf->map.origin.coordinates[X] + start.coordinates[X];
	pixel.coordinates[Y] = fdf->map.origin.coordinates[Y] + start.coordinates[Y];
	while (pixels > 0)
	{
		pixel.color = update_color_gradient(start.color, end.color, len, len - pixels);
		if ((int)(pixel.coordinates[X]) <= WIDTH && (int)(pixel.coordinates[X]) >= 0 && (int)(pixel.coordinates[Y]) <= HEIGHT && (int)(pixel.coordinates[Y]) >= 0)
			faster_pixel_put(&fdf->bitmap, (int)(pixel.coordinates[X]), (int)(pixel.coordinates[Y]), pixel.color);
		pixel.coordinates[X] += delta.coordinates[X];
		pixel.coordinates[Y] += delta.coordinates[Y];
		pixels--;
	}
}

void	draw_lines(t_vars *fdf, t_point **projection)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->map.limits[Y])
	{
		x = -1;
		while (++x < fdf->map.limits[X])
		{
			if (x != fdf->map.limits[X] - 1)
				connect_points(fdf, projection[y][x], projection[y][x + 1]);
			if (y != fdf->map.limits[Y] - 1)
				connect_points(fdf, projection[y][x], projection[y + 1][x]);
		}
	}
}

void	draw_map(t_vars *fdf)
{
	t_point	**projection;
	int		y;

	projection = malloc(sizeof (t_point *) * fdf->map.limits[Y]);
	y = -1;
	while (++y < fdf->map.limits[Y])
		projection[y] = malloc(sizeof (t_point) * fdf->map.limits[X]);
	copy_map(&projection, fdf->map);
	if (fdf->map.spherical)
		spherize(&fdf->map, projection);
	rotatex(&fdf->map, projection, fdf->map.angles[X]);
	rotatey(&fdf->map, projection, fdf->map.angles[Y]);
	rotatez(&fdf->map, projection, fdf->map.angles[Z]);
	orthographic(&fdf->map, projection);
	draw_lines(fdf, projection);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap.img, 0, 0);
	free_projection(projection, fdf->map);
}
