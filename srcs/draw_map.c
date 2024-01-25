/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/25 17:52:03 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_points(t_vars *fdf, t_point start, t_point end)
{
	float	x_variation;
	float	y_variation;
	float	slope;
	int		decision;
	t_point	tmp;

	if (start.coordinates[X] > end.coordinates[X])
	{
		tmp = end;
		end = start;
	}
	else
		tmp = start;
	x_variation = round(fdf->map.origin.coordinates[X] + (end.coordinates[X])) - round(fdf->map.origin.coordinates[X] + (tmp.coordinates[X]));
	y_variation = round(fdf->map.origin.coordinates[Y] + (end.coordinates[Y])) - round(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y]));
	slope = y_variation / x_variation;
	if (slope >= -1 && slope <= 1)
		decision = (2 * abs((int)y_variation)) - abs((int)x_variation);
	else
		decision = (2 * abs((int)x_variation)) - abs((int)y_variation);
	while (round(fdf->map.origin.coordinates[X] + (tmp.coordinates[X])) != round(fdf->map.origin.coordinates[X] + (end.coordinates[X])) || round(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y])) != round(fdf->map.origin.coordinates[Y] + (end.coordinates[Y])))
	{
		if (slope >= -1 && slope <= 1)
		{
			if (decision > 0)
			{
				tmp.coordinates[X]++;
				if (slope >= 0)
					tmp.coordinates[Y]++;
				else
					tmp.coordinates[Y]--;
				decision += (2 * abs((int)y_variation)) - (2 * abs((int)x_variation));
			}
			else
			{
				tmp.coordinates[X]++;
				decision += (2 * abs((int)y_variation));
			}
		}
		else
		{
			if (decision > 0)
			{
				if (slope != INFINITY)
					tmp.coordinates[X]++;
				if (slope >= 0)
					tmp.coordinates[Y]++;
				else
					tmp.coordinates[Y]--;
				decision += (2 * abs((int)x_variation)) - (2 * abs((int)y_variation));
			}
			else
			{
				if (slope >= 0)
					tmp.coordinates[Y]++;
				else
					tmp.coordinates[Y]--;
				decision += (2 * abs((int)x_variation));
			}
		}
		if ((int)(fdf->map.origin.coordinates[X] + (tmp.coordinates[X])) <= WIDTH && (int)(fdf->map.origin.coordinates[X] + (tmp.coordinates[X])) >= 0 && (int)(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y])) <= HEIGHT && (int)(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y])) >= 0)
			faster_pixel_put(&fdf->bitmap, (int)(fdf->map.origin.coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
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
		while (++x < fdf->map.limits[X] - 1)
		{
			connect_points(fdf, projection[y][x], projection[y][x + 1]);
			if (y < fdf->map.limits[Y] - 1)
				connect_points(fdf, projection[y][x], projection[y + 1][x]);
		}
		if (y < fdf->map.limits[Y] - 1)
			connect_points(fdf, projection[y][x], projection[y + 1][x]);
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
	copy_map(projection, fdf->map);
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
			{
				printf("Color White: %d\n", WHITE);
				printf("Color Blue: %d\n", FULL_BLUE);
				printf("Color Green: %d\n", FULL_GREEN);
				printf("Point color: %d\n", projection[y][x].color);
				faster_pixel_put(&fdf->bitmap, (int)(fdf->map.origin.coordinates[X] + (projection[y][x].coordinates[X])), (int)(fdf->map.origin.coordinates[Y] + (projection[y][x].coordinates[Y])), projection[x][y].color);
			}
	}
	draw_lines(fdf, projection);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap.img, 0, 0);
}
