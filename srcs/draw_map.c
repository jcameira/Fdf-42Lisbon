/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/19 18:15:41 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    connect_points(t_vars *fdf, t_point start, t_point end)
{
    float   x_variation;
    float   y_variation;
    float   slope;
    int     decision;
    t_point tmp;

    if (start.coordinates[X] > end.coordinates[X])
    {
        tmp = end;
        end = start;
    }
    else
        tmp = start;
    x_variation = (int)(fdf->map->origin->coordinates[X] + (end.coordinates[X])) - (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X]));
    y_variation = (int)(fdf->map->origin->coordinates[Y] + (end.coordinates[Y])) - (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y]));
    slope = y_variation / x_variation;
    decision = (2 * abs((int)y_variation)) - abs((int)x_variation);
    while ((int)tmp.coordinates[X] != (int)end.coordinates[X] || (int)tmp.coordinates[Y] != (int)end.coordinates[Y])
    {
        printf("\nSlope of %f, with decision variable of %d and X Y Z: %f %f %f\n", slope, decision, tmp.coordinates[X], tmp.coordinates[Y], tmp.coordinates[Z]);
        printf("Slope of %f, with decision variable of %d and X Y Z: %f %f %f\n\n", slope, decision, end.coordinates[X], end.coordinates[Y], end.coordinates[Z]);
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
        faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
    }
}

void    draw_lines(t_vars *fdf)
{
    int x;
    int y;

    y = -1;
    while (++y < fdf->map->limits[Y])
    {
        x = -1;
        while (++x < fdf->map->limits[X] - 1)
        {
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

    rotatex(fdf->map, fdf->map->angles[X]);
    rotatey(fdf->map, fdf->map->angles[Y]);
    rotatez(fdf->map, fdf->map->angles[Z]);
    orthographic(fdf->map);
    y = -1;
    while (++y < fdf->map->limits[Y])
    {
        x = -1;
        while (++x < fdf->map->limits[X])
            faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (fdf->map->points[y][x].coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (fdf->map->points[y][x].coordinates[Y])), 0xFFFFFFFF);
    }
    draw_lines(fdf);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap->img, 0, 0);
}
