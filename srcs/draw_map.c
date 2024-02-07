/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/07 21:32:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_points(t_vars *fdf, t_point start, t_point end)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;

	delta.coordinates[X] = end.coordinates[X] - start.coordinates[X];
	delta.coordinates[Y] = end.coordinates[Y] - start.coordinates[Y];
	pixels = sqrt((delta.coordinates[X] * delta.coordinates[X]) + \
			(delta.coordinates[Y] * delta.coordinates[Y]));
	printf("Pixels: %d\n", pixels);
	delta.coordinates[X] /= pixels;
	delta.coordinates[Y] /= pixels;
	pixel.coordinates[X] = start.coordinates[X];
	pixel.coordinates[Y] = start.coordinates[Y];
	while (pixels > 0)
	{
		update_color_gradient(&start, &end, pixels);
		pixel.coordinates[X] += delta.coordinates[X];
		pixel.coordinates[Y] += delta.coordinates[Y];
		if ((int)(fdf->map.origin.coordinates[X] + pixel.coordinates[X]) <= WIDTH && (int)(fdf->map.origin.coordinates[X] + pixel.coordinates[X]) >= 0 && (int)(fdf->map.origin.coordinates[Y] + pixel.coordinates[Y]) <= HEIGHT && (int)(fdf->map.origin.coordinates[Y] + pixel.coordinates[Y]) >= 0)
			faster_pixel_put(&fdf->bitmap, (int)(fdf->map.origin.coordinates[X] + (pixel.coordinates[X])), (int)(fdf->map.origin.coordinates[Y] + (pixel.coordinates[Y])), start.color);
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
	int		x;
	int		y;

	projection = malloc(sizeof (t_point *) * fdf->map.limits[Y]);
	y = -1;
	while (++y < fdf->map.limits[Y])
		projection[y] = malloc(sizeof (t_point) * fdf->map.limits[X]);
	copy_map(&projection, fdf->map);
	rotatex(&fdf->map, projection, fdf->map.angles[X]);
	rotatey(&fdf->map, projection, fdf->map.angles[Y]);
	rotatez(&fdf->map, projection, fdf->map.angles[Z]);
	orthographic(&fdf->map, projection);
	y = -1;
	while (++y < fdf->map.limits[Y])
	{
		x = -1;
		while (++x < fdf->map.limits[X])
			if ((int)(fdf->map.origin.coordinates[X] + (projection[y][x].coordinates[X])) <= WIDTH && (int)(fdf->map.origin.coordinates[X] + (projection[y][x].coordinates[X])) >= 0 && (int)(fdf->map.origin.coordinates[Y] + (projection[y][x].coordinates[Y])) <= HEIGHT && (int)(fdf->map.origin.coordinates[Y] + (projection[y][x].coordinates[Y])) >= 0)
				faster_pixel_put(&fdf->bitmap, (int)(fdf->map.origin.coordinates[X] + (projection[y][x].coordinates[X])), (int)(fdf->map.origin.coordinates[Y] + (projection[y][x].coordinates[Y])), projection[y][x].color);
	}
	draw_lines(fdf, projection);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap.img, 0, 0);
	free_projection(projection, fdf->map);
}
