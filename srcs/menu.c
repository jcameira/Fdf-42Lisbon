/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:23:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/12 01:30:57 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_info(t_vars *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 30, 30, 0xFFFFFFFF, "MAP INFORMATION");
	mlx_string_put(fdf->mlx, fdf->win, 30, 60, 0xFFFFFFFF, "Number of points");
	mlx_string_put(fdf->mlx, fdf->win, 30, 90, 0xFFFFFFFF, "X limit");
	mlx_string_put(fdf->mlx, fdf->win, 30, 120, 0xFFFFFFFF, "Y limit");
}

void	draw_menu(t_vars *fdf)
{
	int		x;
	int		y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < 350)
			faster_pixel_put(&fdf->bitmap, x, y, 0xFF151515);
	}
	put_info(fdf);
}
