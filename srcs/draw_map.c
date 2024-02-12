/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/12 12:51:56 by jcameira         ###   ########.fr       */
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

	//printf("Start paint and End paint: %d %d\n", start.paint, end.paint);
	if (!inside_window(fdf, start) && !inside_window(fdf, end))
		return ;
	delta.coordinates[X] = (fdf->map.origin.coordinates[X] + end.coordinates[X]) - (fdf->map.origin.coordinates[X] + start.coordinates[X]);
	delta.coordinates[Y] = (fdf->map.origin.coordinates[Y] + end.coordinates[Y]) - (fdf->map.origin.coordinates[Y] + start.coordinates[Y]);
	pixels = sqrt((delta.coordinates[X] * delta.coordinates[X]) + \
			(delta.coordinates[Y] * delta.coordinates[Y]));
	len = pixels;
	delta.coordinates[X] /= pixels;
	delta.coordinates[Y] /= pixels;
	pixel.coordinates[X] = fdf->map.origin.coordinates[X] + start.coordinates[X];
	pixel.coordinates[Y] = fdf->map.origin.coordinates[Y] + start.coordinates[Y];
	while (pixels > 0)
	{
		pixel.color = update_color_gradient(start.color, end.color, len, len - pixels);	
		if (start.paint && end.paint && (int)(pixel.coordinates[X]) <= WIDTH && (int)(pixel.coordinates[X]) >= 0 && (int)(pixel.coordinates[Y]) <= HEIGHT && (int)(pixel.coordinates[Y]) >= 0)
		{
			if ((int)(pixel.coordinates[X]) <= 350 && (int)(pixel.coordinates[X]) >= 0)
				behind_menu(&pixel);
			faster_pixel_put(&fdf->bitmap, (int)(pixel.coordinates[X]), (int)(pixel.coordinates[Y]), pixel.color);
		}
			//mlx_pixel_put(fdf->mlx, fdf->win, (int)(pixel.coordinates[X]), (int)(pixel.coordinates[Y]), pixel.color);
		pixel.coordinates[X] += delta.coordinates[X];
		pixel.coordinates[Y] += delta.coordinates[Y];
		pixels--;
	}
}

void	draw_lines(t_vars *fdf, t_point **projection)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.limits[Y])
	{
		x = 0;
		while (x < fdf->map.limits[X])
		{
			//printf("point paint: %d\n", projection[y][x].paint);
			if (x + fdf->map.point_density >= fdf->map.limits[X])
				connect_points(fdf, projection[y][x], projection[y][fdf->map.limits[X] - 1]);
			else if (x != fdf->map.limits[X] - 1)
				connect_points(fdf, projection[y][x], projection[y][x + fdf->map.point_density]);
			if (y + fdf->map.point_density >= fdf->map.limits[Y])
				connect_points(fdf, projection[y][x], projection[fdf->map.limits[Y] - 1][x]);	
			else if (y != fdf->map.limits[Y] - 1)
				connect_points(fdf, projection[y][x], projection[y + fdf->map.point_density][x]);
			x += fdf->map.point_density;
		}
		y += fdf->map.point_density;
	}
}

void	hide_back_sphere(t_map *map, t_point **projection)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			if (projection[y][x].coordinates[Z] < 0)
				projection[y][x].paint = 0;
	}
}

void	draw_map(t_vars *fdf)
{
	t_point	**projection;

	projection = copy_map(fdf->map);
	if (fdf->map.spherical)
		spherize(&fdf->map, projection);
	rotatex(&fdf->map, projection, fdf->map.angles[X]);
	rotatey(&fdf->map, projection, fdf->map.angles[Y]);
	rotatez(&fdf->map, projection, fdf->map.angles[Z]);
	if (fdf->map.spherical)
		hide_back_sphere(&fdf->map, projection);
	orthographic(&fdf->map, projection);
	draw_lines(fdf, projection);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap.img, 0, 0);
	free_projection(projection, fdf->map);
}
