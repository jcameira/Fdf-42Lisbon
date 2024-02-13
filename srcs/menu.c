/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:23:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/13 01:37:56 by jcameira         ###   ########.fr       */
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
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_X);
	tmp = TO_STR(X_LIM);
	mlx_string_put(MLX, WIN, X_END(INFO_X), y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_Y);
	tmp = TO_STR(Y_LIM);
	mlx_string_put(MLX, WIN, X_END(INFO_Y), y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_ZMAX);
	tmp = TO_STR(ZMAX);
	mlx_string_put(MLX, WIN, X_END(INFO_ZMAX), y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, INFO_ZMIN);
	tmp = TO_STR(ZMIN);
	mlx_string_put(MLX, WIN, X_END(INFO_ZMIN), y, NBR_YELLOW, tmp);
	free(tmp);
}

void	put_frame_details(t_vars *fdf)
{
	int		y;
	char	*tmp;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, DETAILS);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y) + 7, WHITE, ANGLES);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y) - 8, WHITE, SPACES);
	tmp = TO_STR(X_ANGLE);
	mlx_string_put(MLX, WIN, X_SPACE, y - 9, NBR_YELLOW, tmp);
	free(tmp);
	tmp = TO_STR(Y_ANGLE);
	mlx_string_put(MLX, WIN, Y_SPACE, y - 9, NBR_YELLOW, tmp);
	free(tmp);
	tmp = TO_STR(Z_ANGLE);
	mlx_string_put(MLX, WIN, Z_SPACE, y - 9, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, ZOOM);
	tmp = FTO_STR(SCALE);
	mlx_string_put(MLX, WIN, Z_SPACE, y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, Z_MUL);
	tmp = FTO_STR(Z_VAL_MUL);
	mlx_string_put(MLX, WIN, Z_SPACE, y, NBR_YELLOW, tmp);
	free(tmp);
}
void	choose_str_color(t_vars *fdf, int x, int y, char *str, int flag)
{
	if (flag)
		mlx_string_put(MLX, WIN, x, y, SELECTION, str);
	else
		mlx_string_put(MLX, WIN, x, y, WHITE, str);
}

void	put_controls(t_vars *fdf)
{
	int	y;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, SCHEME);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_DEFAULT);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), SELECTION, STR_EARTH);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_MONO_W);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, NEG_OFF);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_ISOMETRIC,
		fdf->map.projection == ISOMETRIC);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_TOP_VIEW,
		fdf->map.projection == TOP_VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_SIDE_VIEW,
		fdf->map.projection == SIDE_VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_FRONT_VIEW,
		fdf->map.projection == FRONT_VIEW);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_CONIC,
		fdf->map.projection == CONIC);
	choose_str_color(fdf, X_START, NEXT_LINE(y), STR_SPHERE,
		fdf->map.projection == SPHERE);
}

void	draw_menu(t_vars *fdf)
{
	put_info(fdf);
	put_frame_details(fdf);
	put_controls(fdf);
}

void	menu_background(t_vars *fdf)
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
}
