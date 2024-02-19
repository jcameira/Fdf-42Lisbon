/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 01:23:28 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 15:47:54 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_menu(t_vars *fdf)
{
	int	y;

	y = Y_START;
	put_info(fdf, &y);
	put_angles(fdf, &y);
	put_zoom_vel(fdf, &y);
	put_scheme(fdf, &y);
	put_proj(fdf, &y);
	put_controls(fdf, &y);
	put_in_use_name(fdf, &y);
}

void	menu_background(t_vars *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < MENU_WIDTH)
			faster_pixel_put(&fdf->bitmap, x, y, MENU_BACKGROUND);
	}
}

void	menu_button(t_vars *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= 15)
	{
		if (fdf->menu)
		{
			x = 349;
			while (++x < 365)
				faster_pixel_put(&fdf->bitmap, x, y, BUTTON);
		}
		else
		{
			x = -1;
			while (++x < 15)
				faster_pixel_put(&fdf->bitmap, x, y, BUTTON);
		}
	}
	if (fdf->menu)
		mlx_string_put(fdf->mlx, fdf->win, 355, 12, BUTTON_STR, "<");
	else
		mlx_string_put(fdf->mlx, fdf->win, 5, 12, BUTTON_STR, ">");
}
