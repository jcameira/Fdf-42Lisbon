/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/01 16:28:15 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham_var_assign(t_point *tmp, t_point *start, t_point *end)
{
	if ((*start).coordinates[X] > (*end).coordinates[X])
	{
		(*tmp) = *end;
		*end = *start;
	}
	else
		(*tmp) = *start;
}

void	bresenham_ls(t_point *tmp, int *decision, float x_variation, float y_variation)
{
	if (*decision > 0)
	{
		(*tmp).coordinates[X]++;
		if (y_variation / x_variation >= 0)
			(*tmp).coordinates[Y]++;
		else
			(*tmp).coordinates[Y]--;
		*decision += (2 * abs((int)y_variation)) - (2 * abs((int)x_variation));
	}
	else
	{
		(*tmp).coordinates[X]++;
		*decision += (2 * abs((int)y_variation));
	}
}

void	bresenham_hs(t_point *tmp, int *decision, float x_variation, float y_variation)
{
	if (*decision > 0)
	{
		if (y_variation / x_variation != INFINITY)
			(*tmp).coordinates[X]++;
		if (y_variation / x_variation >= 0)
			(*tmp).coordinates[Y]++;
		else
			(*tmp).coordinates[Y]--;
		*decision += (2 * abs((int)x_variation)) - (2 * abs((int)y_variation));
	}
	else
	{
		if (y_variation / x_variation >= 0)
			(*tmp).coordinates[Y]++;
		else
			(*tmp).coordinates[Y]--;
		*decision += (2 * abs((int)x_variation));
	}
}

int	connect_points(t_vars *fdf, t_point start, t_point end, int flag)
{
	float	x_variation;
	float	y_variation;
	int		decision;
	int		pixels;
	t_point	tmp;

	bresenham_var_assign(&tmp, &start, &end);
	//set_color_increments(&tmp, end);
	x_variation = round(fdf->map.origin.coordinates[X] + (end.coordinates[X])) - round(fdf->map.origin.coordinates[X] + (tmp.coordinates[X]));
	y_variation = round(fdf->map.origin.coordinates[Y] + (end.coordinates[Y])) - round(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y]));
	if (y_variation / x_variation >= -1 && y_variation / x_variation <= 1)
		decision = (2 * abs((int)y_variation)) - abs((int)x_variation);
	else
		decision = (2 * abs((int)x_variation)) - abs((int)y_variation);
	pixels = 0;
	while (round(fdf->map.origin.coordinates[X] + (tmp.coordinates[X])) != round(fdf->map.origin.coordinates[X] + (end.coordinates[X])) || round(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y])) != round(fdf->map.origin.coordinates[Y] + (end.coordinates[Y])))
	{
		if (y_variation / x_variation >= -1 && y_variation / x_variation <= 1)
			bresenham_ls(&tmp, &decision, x_variation, y_variation);
		else
			bresenham_hs(&tmp, &decision, x_variation, y_variation);
		pixels++;
		//update_color(&tmp);
		if (flag && (int)(fdf->map.origin.coordinates[X] + tmp.coordinates[X]) <= WIDTH && (int)(fdf->map.origin.coordinates[X] + tmp.coordinates[X]) >= 0 && (int)(fdf->map.origin.coordinates[Y] + tmp.coordinates[Y]) <= HEIGHT && (int)(fdf->map.origin.coordinates[Y] + tmp.coordinates[Y]) >= 0)
			faster_pixel_put(&fdf->bitmap, (int)(fdf->map.origin.coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map.origin.coordinates[Y] + (tmp.coordinates[Y])), tmp.color);
	}
	return (pixels);
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
			//projection[y][x].nmr_pixels_next_point = connect_points(fdf, projection[y][x], projection[y][x + 1], 0);
			connect_points(fdf, projection[y][x], projection[y][x + 1], 1);
			if (y < fdf->map.limits[Y] - 1)
			{
				//projection[y][x].nmr_pixels_next_point = connect_points(fdf, projection[y][x], projection[y + 1][x], 0);
				connect_points(fdf, projection[y][x], projection[y + 1][x], 1);
			}
		}
		if (y < fdf->map.limits[Y] - 1)
		{
			//projection[y][x].nmr_pixels_next_point = connect_points(fdf, projection[y][x], projection[y + 1][x], 0);
			connect_points(fdf, projection[y][x], projection[y + 1][x], 1);
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
