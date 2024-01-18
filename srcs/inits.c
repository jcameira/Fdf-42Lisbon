/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:34:32 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/18 13:25:15 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vars	*vars_init(char *title)
{
	t_vars		*fdf;

	fdf = malloc(sizeof(t_vars));
	fdf->bitmap = malloc(sizeof(t_bitmap));
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, title);
	fdf->bitmap->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->bitmap->address = mlx_get_data_addr(fdf->bitmap->img,
			&fdf->bitmap->bits_per_pixel, &fdf->bitmap->line_length,
			&fdf->bitmap->endian);
	return (fdf);
}

t_map   *map_init(void)
{
    t_map   *map;

    map = malloc(sizeof (t_map));
    if (!map)
        return (NULL);
    map->projection = ISOMETRIC;
    map->scale = 1;
    map->angles[X] = 30;
    map->angles[Y] = 30;
    map->angles[Z] = -45;
    map->origin = malloc(sizeof (t_point));
    if (!map->origin)
        return (NULL);
    map->origin->coordinates[X] = WIDTH/2;
    map->origin->coordinates[Y] = HEIGHT/2;
    map->origin->coordinates[Z] = 0;
    return (map);
}
