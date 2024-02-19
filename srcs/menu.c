/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:23:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 01:41:34 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_info(t_vars *fdf, int *y)
{
	char	*tmp;

	mlx_string_put(fdf->mlx, fdf->win, X_START, *y, WHITE, INFO);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, INFO_SIZE);
	tmp = ft_itoa(fdf->map[fdf->in_use].lim[X] * fdf->map[fdf->in_use].lim[Y]);
	mlx_string_put(fdf->mlx, fdf->win, x_end(INFO_SIZE), *y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, INFO_X_Y);
	tmp = ft_itoa(fdf->map[fdf->in_use].lim[X]);
	mlx_string_put(fdf->mlx, fdf->win, x_end(INFO_X), *y, NBR_YELLOW, tmp);
	free(tmp);
	tmp = ft_itoa(fdf->map[fdf->in_use].lim[Y]);
	mlx_string_put(fdf->mlx, fdf->win, x_end(INFO_X_Y), *y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y),
		WHITE, INFO_ZMAX_ZMIN);
	tmp = ft_itoa(fdf->map[fdf->in_use].z_min);
	mlx_string_put(fdf->mlx, fdf->win, x_end(INFO_ZMIN), *y, NBR_YELLOW, tmp);
	free(tmp);
	tmp = ft_itoa(fdf->map[fdf->in_use].z_max);
	mlx_string_put(fdf->mlx, fdf->win, x_end(INFO_ZMAX_ZMIN),
		*y, NBR_YELLOW, tmp);
	free(tmp);
}

void	put_scheme(t_vars *fdf, int *y)
{
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, SCHEME);
	choose_str_color(fdf, next_line(y), STR_DEFAULT,
		fdf->map[fdf->in_use].scheme == DEFAULT);
	choose_str_color(fdf, next_line(y), STR_EARTH,
		fdf->map[fdf->in_use].scheme == EARTH);
	choose_str_color(fdf, next_line(y), STR_BLUEISH_TONES,
		fdf->map[fdf->in_use].scheme == BLUEISH_TONES);
	choose_str_color(fdf, next_line(y), STR_SOFTER_TONES,
		fdf->map[fdf->in_use].scheme == SOFTER_TONES);
	choose_str_color(fdf, next_line(y), STR_BRIGHT_TONES,
		fdf->map[fdf->in_use].scheme == BRIGHT_TONES);
	choose_str_color(fdf, next_line(y), STR_HIGH_CONTRAST,
		fdf->map[fdf->in_use].scheme == HIGH_CONTRAST);
	choose_str_color(fdf, next_line(y), STR_ANOTHER_EARTH,
		fdf->map[fdf->in_use].scheme == ANOTHER_EARTH);
	choose_str_color(fdf, next_line(y), STR_BRIGHT_PASTEL,
		fdf->map[fdf->in_use].scheme == BRIGHT_PASTEL);
	choose_str_color(fdf, next_line(y), STR_PINKISH_PASTEL,
		fdf->map[fdf->in_use].scheme == PINKISH_PASTEL);
	if (fdf->map[fdf->in_use].inverted)
		mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), SELECTION,
			NEG_ON);
	else
		mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y),
			WHITE, NEG_OFF);
}

void	put_proj(t_vars *fdf, int *y)
{
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, VIEW);
	choose_str_color(fdf, next_line(y), STR_ISOMETRIC,
		fdf->map[fdf->in_use].proj == ISOMETRIC);
	choose_str_color(fdf, next_line(y), STR_TOP_VIEW,
		fdf->map[fdf->in_use].proj == TOP_VIEW);
	choose_str_color(fdf, next_line(y), STR_SIDE_VIEW,
		fdf->map[fdf->in_use].proj == SIDE_VIEW);
	choose_str_color(fdf, next_line(y), STR_FRONT_VIEW,
		fdf->map[fdf->in_use].proj == FRONT_VIEW);
	choose_str_color(fdf, next_line(y), STR_CONIC,
		fdf->map[fdf->in_use].proj == CONIC);
	choose_str_color(fdf, next_line(y), STR_SPHERE,
		fdf->map[fdf->in_use].proj == SPHERE);
}

void	put_controls(t_vars *fdf, int *y)
{
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, CONTROLS);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		TRANSLATION);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, ARROWS);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		LMOUSE_ROT);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		RMOUSE_ROT);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, X_ROT);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, Y_ROT);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, Z_ROT);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, MOUSE_W);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, S_MOUSE_W);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, C_MOUSE_W);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, A_MOUSE_W);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		PROJ_CHANGE);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, ROT_VEL);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		TRANSLATION_VEL);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, SCALE_VEL);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, INVERT);
}

void	put_in_use_name(t_vars *fdf, int *y)
{
	int	button_y;
	int	x;

	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, MAP_NAME);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		fdf->map[fdf->in_use].name);
	button_y = *y - 12;
	while (++button_y < *y + 3)
	{
		x = 299;
		while (++x < 315)
			faster_pixel_put(&fdf->bitmap, x, button_y, BUTTON);
		x = 319;
		while (++x < 335)
			faster_pixel_put(&fdf->bitmap, x, button_y, BUTTON);
	}
	mlx_string_put(fdf->mlx, fdf->win, x - 10, *y, BUTTON_STR, ">");
	mlx_string_put(fdf->mlx, fdf->win, x - 30, *y, BUTTON_STR, "<");
}
