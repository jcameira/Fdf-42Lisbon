/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/18 19:38:00 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    connect_points(t_vars *fdf, t_point start, t_point end)
{
    float   x_variation;
    float   y_variation;
    float   slope;
    float     decision;
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
    decision = (2 * y_variation) - x_variation;
    if (slope >= 0)
    {
        if (slope <= 1)
        {
            while ((int)tmp.coordinates[X] != (int)end.coordinates[X] || (int)tmp.coordinates[Y] != (int)end.coordinates[Y])
            {
                printf("Positive slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + tmp.coordinates[X], fdf->map->origin->coordinates[Y] + tmp.coordinates[Y], tmp.coordinates[Z]);
                printf("Positive slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + end.coordinates[X], fdf->map->origin->coordinates[Y] + end.coordinates[Y], end.coordinates[Z]);
                printf("Decision: %f\n", decision);
                if (decision > 0)
                {
                    tmp.coordinates[X]++;
                    tmp.coordinates[Y]++;
                    faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
                    decision += (2 * y_variation) - (2 * x_variation);
                }
                else
                {
                    tmp.coordinates[X]++;
                    faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
                    decision += (2 * y_variation);
                }
            }
        }
        if (slope > 1)
        {
            while ((int)tmp.coordinates[X] != (int)end.coordinates[X] || (int)tmp.coordinates[Y] != (int)end.coordinates[Y])
            {
                printf("Positive slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + tmp.coordinates[X], fdf->map->origin->coordinates[Y] + tmp.coordinates[Y], tmp.coordinates[Z]);
                printf("Positive slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + end.coordinates[X], fdf->map->origin->coordinates[Y] + end.coordinates[Y], end.coordinates[Z]);
                printf("Decision: %f\n", decision);
                if (decision > 0)
                {
                    tmp.coordinates[X]++;
                    tmp.coordinates[Y]++;
                    faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
                    decision += (2 * x_variation) - (2 * y_variation);
                }
                else
                {
                    tmp.coordinates[Y]++;
                    faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
                    decision += (2 * x_variation);
                }
            }
        }
    }
    // else
    // {
    //     if (slope >= -1)
    //     {
    //         while ((int)tmp.coordinates[X] != (int)end.coordinates[X] || (int)tmp.coordinates[Y] != (int)end.coordinates[Y])
    //         {
    //             printf("Negative slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + tmp.coordinates[X], fdf->map->origin->coordinates[Y] + tmp.coordinates[Y], tmp.coordinates[Z]);
    //             printf("Negative slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + end.coordinates[X], fdf->map->origin->coordinates[Y] + end.coordinates[Y], end.coordinates[Z]);
    //             printf("Decision: %f\n", decision);
    //             if (decision > 0)
    //             {
    //                     tmp.coordinates[X]++;
    //                     tmp.coordinates[Y]--;
    //                 printf("Point to be put %f, %f\n", fdf->map->origin->coordinates[X] + (tmp.coordinates[X]), fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y]));
    //                 faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
    //                 decision += (2 * x_variation) - (2 * y_variation);
    //             }
    //             else
    //             {
    //                     tmp.coordinates[X]++;
    //                 faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
    //                 decision += (2 * x_variation);
    //             }
    //         }
    //     }
    //     if (slope < -1)
    //     {
    //         while ((int)tmp.coordinates[X] != (int)end.coordinates[X] || (int)tmp.coordinates[Y] != (int)end.coordinates[Y])
    //         {
    //             printf("Positive slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + tmp.coordinates[X], fdf->map->origin->coordinates[Y] + tmp.coordinates[Y], tmp.coordinates[Z]);
    //             printf("Positive slope of %f X Y Z: %f %f %f\n", slope, fdf->map->origin->coordinates[X] + end.coordinates[X], fdf->map->origin->coordinates[Y] + end.coordinates[Y], end.coordinates[Z]);
    //             printf("Decision: %f\n", decision);
    //             if (decision > 0)
    //             {
    //                     tmp.coordinates[X]++;
    //                     tmp.coordinates[Y]--;
    //                 faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
    //                 decision += (2 * x_variation) - (2 * y_variation);
    //             }
    //             else
    //             {
    //                     tmp.coordinates[Y]--;
    //                 faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (tmp.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (tmp.coordinates[Y])), 0xFFFFFFFF);
    //                 decision += (2 * x_variation);
    //             }
    //         }
    //     }
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
            printf("From point %d, %d to point %d, %d\n", y, x, y, x + 1);
            connect_points(fdf, fdf->map->points[y][x], fdf->map->points[y][x + 1]);
            if (y < fdf->map->limits[Y] - 1)
            {
                printf("From point %d, %d to point %d, %d\n", y, x, y + 1, x);
                connect_points(fdf, fdf->map->points[y][x], fdf->map->points[y + 1][x]);
            }
        }
        if (y < fdf->map->limits[Y] - 1)
        {
            printf("From point %d, %d to point %d, %d\n", y, x, y + 1, x);
            connect_points(fdf, fdf->map->points[y][x], fdf->map->points[y + 1][x]);
        }
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
        {
            printf("I, J: %d, %d\n", y, x);
            printf("X Y Z: %f %f %f\n", fdf->map->origin->coordinates[X] + fdf->map->points[y][x].coordinates[X], fdf->map->origin->coordinates[Y] + fdf->map->points[y][x].coordinates[Y], fdf->map->points[y][x].coordinates[Z]);
            faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (fdf->map->points[y][x].coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (fdf->map->points[y][x].coordinates[Y])), 0xFFFFFFFF);
        }
    }
    draw_lines(fdf);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap->img, 0, 0);
}
