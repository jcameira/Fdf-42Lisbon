/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:23:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/16 20:53:38 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_info(t_vars *fdf)
{
	int		y;
	char	*tmp;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_SIZE);
	tmp = TO_STR(SIZE);
	mlx_string_put(MLX, WIN, X_END(INFO_SIZE), y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_X_Y);
	tmp = TO_STR(X_LIM);
	mlx_string_put(MLX, WIN, X_END(INFO_X), y, NBR_YELLOW, tmp);
	free(tmp);
	// mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_Y);
	tmp = TO_STR(Y_LIM);
	mlx_string_put(MLX, WIN, X_END(INFO_X_Y), y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_ZMAX_ZMIN);
	tmp = TO_STR(ZMAX);
	mlx_string_put(MLX, WIN, X_END(INFO_ZMAX), y, NBR_YELLOW, tmp);
	free(tmp);
	//mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_ZMIN);
	tmp = TO_STR(ZMIN);
	mlx_string_put(MLX, WIN, X_END(INFO_ZMAX_ZMIN), y, NBR_YELLOW, tmp);
	free(tmp);
}

void	put_frame_details(t_vars *fdf)
{
	int		y;
	char	*tmp;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, DETAILS);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y) + 3, WHITE, ANGLES);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y) - 4, WHITE, SPACES);
	tmp = TO_STR(X_ANGLE);
	mlx_string_put(MLX, WIN, X_SPACE, y - 5, NBR_YELLOW, tmp);
	free(tmp);
	tmp = TO_STR(Y_ANGLE);
	mlx_string_put(MLX, WIN, Y_SPACE, y - 5, NBR_YELLOW, tmp);
	free(tmp);
	tmp = TO_STR(Z_ANGLE);
	mlx_string_put(MLX, WIN, Z_SPACE, y - 5, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, ZOOM);
	tmp = FTO_STR(SCALE);
	mlx_string_put(MLX, WIN, X_END(ZOOM), y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, Z_MUL);
	tmp = FTO_STR(Z_VAL_MUL);
	mlx_string_put(MLX, WIN, X_END(Z_MUL), y, NBR_YELLOW, tmp);
	free(tmp);
}
void	choose_str_color(t_vars *fdf, int x, int y, char *str, int flag)
{
	if (flag)
		mlx_string_put(MLX, WIN, x, y, SELECTION, str);
	else
		mlx_string_put(MLX, WIN, x, y, WHITE, str);
}

void	put_proj_scheme(t_vars *fdf)
{
	int	y;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, SCHEME);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_DEFAULT,
		fdf->map[fdf->in_use].scheme == DEFAULT);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_EARTH,
		fdf->map[fdf->in_use].scheme == EARTH);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_BLUEISH_TONES,
		fdf->map[fdf->in_use].scheme == BLUEISH_TONES);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_SOFTER_TONES,
		fdf->map[fdf->in_use].scheme == SOFTER_TONES);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_BRIGHT_TONES,
		fdf->map[fdf->in_use].scheme == BRIGHT_TONES);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_HIGH_CONTRAST,
		fdf->map[fdf->in_use].scheme == HIGH_CONTRAST);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_ANOTHER_EARTH,
		fdf->map[fdf->in_use].scheme == ANOTHER_EARTH);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_BRIGHT_PASTEL,
		fdf->map[fdf->in_use].scheme == BRIGHT_PASTEL);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_PINKISH_PASTEL,
		fdf->map[fdf->in_use].scheme == PINKISH_PASTEL);
	if (fdf->map[fdf->in_use].inverted)
		mlx_string_put(MLX, WIN, X_START, y + 19, SELECTION, NEG_ON);
	else
		mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, NEG_OFF);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_ISOMETRIC,
		fdf->map[fdf->in_use].proj == ISOMETRIC);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_TOP_VIEW,
		fdf->map[fdf->in_use].proj == TOP_VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_SIDE_VIEW,
		fdf->map[fdf->in_use].proj == SIDE_VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_FRONT_VIEW,
		fdf->map[fdf->in_use].proj == FRONT_VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_CONIC,
		fdf->map[fdf->in_use].proj == CONIC);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_SPHERE,
		fdf->map[fdf->in_use].proj == SPHERE);
}

void	put_controls(t_vars *fdf)
{
	int	y;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, CONTROLS);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, TRANSLATION);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, ARROWS);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, LMOUSE_ROT);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, RMOUSE_ROT);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, X_ROT);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, Y_ROT);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, Z_ROT);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, MOUSE_WHEEL);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, S_MOUSE_WHEEL);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, C_MOUSE_WHEEL);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, A_MOUSE_WHEEL);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, PROJ_CHANGE);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, ROT_VEL);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, TRANSLATION_VEL);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INVERT);
}

void	put_in_use_name(t_vars *fdf)
{
	int	y;
	int	button_y;
	int	x;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, MAP_NAME);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, fdf->map[fdf->in_use].name);
	button_y = y - 12;
	//printf("%d\n", button_y);
	while (++button_y < y + 3)
	{
		x = 299;
		while (++x < 315)
			faster_pixel_put(&fdf->bitmap, x, button_y, 0xFFAAAAAA);
		x = 319;
		while (++x < 335)
			faster_pixel_put(&fdf->bitmap, x, button_y, 0xFFAAAAAA);
	}
	mlx_string_put(MLX, WIN, x - 10, y, 0xFF000000, ">");
	mlx_string_put(MLX, WIN, x - 30, y, 0xFF000000, "<");
}

void	draw_menu(t_vars *fdf)
{
	put_info(fdf);
	put_frame_details(fdf);
	put_proj_scheme(fdf);
	put_controls(fdf);
	put_in_use_name(fdf);
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
			faster_pixel_put(&fdf->bitmap, x, y, 0xFF151515);
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
				faster_pixel_put(&fdf->bitmap, x, y, 0xFFAAAAAA);
		}
		else
		{
			x = -1;
			while (++x < 15)
				faster_pixel_put(&fdf->bitmap, x, y, 0xFFAAAAAA);
		}
	}
	if (fdf->menu)
		mlx_string_put(fdf->mlx, fdf->win, 355, 12, 0xFF000000, "<");
	else
		mlx_string_put(fdf->mlx, fdf->win, 5, 12, 0xFF000000, ">");
}
