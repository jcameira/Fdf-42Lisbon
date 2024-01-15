/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/15 21:59:11 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    connect_points(t_vars *fdf, t_point start, t_point end)
{
    float     x_variation;
    float     y_variation;
    float     slope;
    float     decision;
    t_point tmp;

    tmp = start;
    tmp.coordinates[X] *= 50;
    tmp.coordinates[Y] *= 50;
    end.coordinates[X] *= 50;
    end.coordinates[Y] *= 50;
    x_variation = end.coordinates[X] - tmp.coordinates[X];
    y_variation = end.coordinates[Y] - tmp.coordinates[Y];
    slope = y_variation / x_variation;
    decision = 2 * y_variation - x_variation;
    printf("slope = %f\n", slope);
    printf("Start x, Start y: %f, %f\n", fdf->map->origin->coordinates[X] + tmp.coordinates[X], fdf->map->origin->coordinates[Y] + tmp.coordinates[Y]);
    printf("End x, End y: %f, %f\n", fdf->map->origin->coordinates[X] + end.coordinates[X], fdf->map->origin->coordinates[Y] + end.coordinates[Y]);
    if (slope < 0 && fdf->map->origin->coordinates[X] + tmp.coordinates[X] < fdf->map->origin->coordinates[X] + end.coordinates[X] && fdf->map->origin->coordinates[Y] + tmp.coordinates[Y] < fdf->map->origin->coordinates[Y] + end.coordinates[Y])
    {
        printf("Start x, Start y: %f, %f\n", tmp.coordinates[X], tmp.coordinates[Y]);
        printf("End x, End y: %f, %f\n", end.coordinates[X], end.coordinates[Y]);
        while ((int)(fdf->map->origin->coordinates[X] + tmp.coordinates[X]) != (int)(fdf->map->origin->coordinates[X] + end.coordinates[X]) || (int)(fdf->map->origin->coordinates[Y] + tmp.coordinates[Y]) != (int)(fdf->map->origin->coordinates[Y] + end.coordinates[Y]))
        {
            printf("decision = %f\n", decision);
            if (decision > 0)
            {
                tmp.coordinates[X]++;
                tmp.coordinates[Y]++;
                printf("X, Y = %f, %f\n", tmp.coordinates[X], tmp.coordinates[Y]);
                faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + tmp.coordinates[X]), (int)(fdf->map->origin->coordinates[X] + tmp.coordinates[Y]), 0xFFFFFFFF);
                decision = 2 * y_variation - 2 * x_variation;
            }
            else
            {
                tmp.coordinates[X]++;
                printf("X, Y = %f, %f\n", fdf->map->origin->coordinates[X] + tmp.coordinates[X], fdf->map->origin->coordinates[X] + tmp.coordinates[Y]);
                faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + tmp.coordinates[X]), (int)(fdf->map->origin->coordinates[Y] + tmp.coordinates[Y]), 0xFFFFFFFF);
                decision = 2 * y_variation;
            }
        }
    }
    // {
	// t_point	delta;
	// t_point	pixel;
	// int		pixels;
// 
    // start.coordinates[X] *= 50;
    // start.coordinates[Y] *= 50;
    // end.coordinates[X] *= 50;
    // end.coordinates[Y] *= 50;
	// delta.coordinates[X] = end.coordinates[X] - start.coordinates[X];
	// delta.coordinates[Y] = end.coordinates[Y] - start.coordinates[Y];
	// pixels = sqrt((delta.coordinates[X] * delta.coordinates[X]) + 
			// (delta.coordinates[Y] * delta.coordinates[Y]));
	// delta.coordinates[X] /= pixels;
	// delta.coordinates[Y] /= pixels;
	// pixel.coordinates[X] = start.coordinates[X];
	// pixel.coordinates[Y] = start.coordinates[Y];
	// while (pixels > 0)
	// {
		// faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + pixel.coordinates[X]), (int)(fdf->map->origin->coordinates[X] + pixel.coordinates[Y]), 0xFFFFFFFF);
		// pixel.coordinates[X] += delta.coordinates[X];
		// pixel.coordinates[Y] += delta.coordinates[Y];
		// pixels = pixels - 1;
	// }

}

void    draw_lines(t_vars *fdf)
{
    int x;
    int y;

    printf("Here\n");
    y = -1;
    while (++y < fdf->map->limits[Y])
    {
        x = -1;
        while (++x < fdf->map->limits[X] - 1)
        {
            //printf("Here\n");
            connect_points(fdf, fdf->map->points[y][x], fdf->map->points[y][x + 1]);
            if (y < fdf->map->limits[Y] - 1)
                connect_points(fdf, fdf->map->points[y][x], fdf->map->points[y + 1][x]);
        }
        if (y < fdf->map->limits[Y] - 1)
            connect_points(fdf, fdf->map->points[y][x], fdf->map->points[y + 1][x]);
    }
}

void    draw_map(t_vars *fdf)
{
    int x;
    int y;

    //rotatex(fdf->map, fdf->map->angles[X]);
    //rotatey(fdf->map, fdf->map->angles[Y]);
    rotatez(fdf->map, fdf->map->angles[Z]);
    orthographic(fdf->map);
    y = -1;
    while (++y < fdf->map->limits[Y])
    {
        x = -1;
        while (++x < fdf->map->limits[X])
        {
            printf("I, J: %d, %d\n", y, x);
            printf("X Y Z: %f %f %f\n", fdf->map->origin->coordinates[X] + fdf->map->points[y][x].coordinates[X], fdf->map->origin->coordinates[Y] + fdf->map->points[y][x].coordinates[Y], fdf->map->points[y][x].coordinates[Z]);
            faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (fdf->map->points[y][x].coordinates[X] * 50)), (int)(fdf->map->origin->coordinates[Y] + (fdf->map->points[y][x].coordinates[Y] * 50)), 0xFFFFFFFF);
        }
    }
    draw_lines(fdf);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap->img, 0, 0);
}
