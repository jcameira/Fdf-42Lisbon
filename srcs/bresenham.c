/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:12:04 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/19 17:14:25 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    pos_slope(t_vars *fdf, t_point start, t_point end, float slope)
{
    float   x_variation;
    float   y_variation;
    float   decision;

    x_variation = (int)(fdf->map->origin->coordinates[X] + (end.coordinates[X])) - (int)(fdf->map->origin->coordinates[X] + (start.coordinates[X]));
    y_variation = (int)(fdf->map->origin->coordinates[Y] + (end.coordinates[Y])) - (int)(fdf->map->origin->coordinates[Y] + (start.coordinates[Y]));
    decision = (2 * abs((int)y_variation)) - abs((int)x_variation);
    while ((int)start.coordinates[X] != (int)end.coordinates[X] || (int)start.coordinates[Y] != (int)end.coordinates[Y])
    {
        if (decision > 0)
        {
            start.coordinates[X]++;
            start.coordinates[Y]++;
            if (slope > 1)
                decision += (2 * abs((int)x_variation)) - (2 * abs((int)y_variation));
            else
                decision += (2 * abs((int)y_variation)) - (2 * abs((int)x_variation));
        }
        else
        {
            if (slope > 1)
            {
                start.coordinates[Y]++;
                decision += (2 * abs((int)x_variation));
            }
            else
            {
                start.coordinates[X]++;
                decision += (2 * abs((int)y_variation));
            }
        }
        faster_pixel_put(fdf->bitmap, (int)(fdf->map->origin->coordinates[X] + (start.coordinates[X])), (int)(fdf->map->origin->coordinates[Y] + (start.coordinates[Y])), 0xFFFFFFFF);
    }
}
