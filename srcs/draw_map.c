/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:16:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/13 16:42:39 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_lines(t_map *map)
{
    
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
            faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (fdf->map->points[y][x].coordinates[X] * 50)), (int)(fdf->map->origin->coordinates[Y] + (fdf->map->points[y][x].coordinates[Y] * 50)), 0xFFFFFFFF);
        }
    }
    draw_lines(fdf->map);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->bitmap->img, 0, 0);
}
