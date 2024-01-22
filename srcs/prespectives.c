/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prespectives.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:25:38 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/22 20:50:28 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    isometric(t_vars *fdf)
{
    mlx_destroy_image(fdf->mlx, fdf->bitmap->img);
    fdf->bitmap->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap->address = mlx_get_data_addr(fdf->bitmap->img,
			&fdf->bitmap->bits_per_pixel, &fdf->bitmap->line_length,
			&fdf->bitmap->endian);
    fdf->map->angles[X] = 30;
    fdf->map->angles[Y] = 330;
    fdf->map->angles[Z] = 45;
    draw_map(fdf);
}

void    top_view(t_vars *fdf)
{
    mlx_destroy_image(fdf->mlx, fdf->bitmap->img);
    fdf->bitmap->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap->address = mlx_get_data_addr(fdf->bitmap->img,
			&fdf->bitmap->bits_per_pixel, &fdf->bitmap->line_length,
			&fdf->bitmap->endian);
    fdf->map->angles[X] = 30;
    fdf->map->angles[Y] = 330;
    fdf->map->angles[Z] = 45;
    draw_map(fdf);
}

void    choose_prespective(t_vars *fdf, int  prespective)
{
    if (prespective == 0)
        isometric(fdf);
    if (prespective == 1)
        top_view(fdf);
}