/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:23:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/12 21:12:16 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_info(t_vars *fdf)
{
	int	y;
	char *tmp;

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
	int	y;
	char *tmp;

	y = Y_START;
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, DETAILS);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, ANGLES);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, SPACES);
	tmp = TO_STR(X_ANGLE);
	mlx_string_put(MLX, WIN, X_SPACE, y - 1, NBR_YELLOW, tmp);
	free(tmp);
	tmp = TO_STR(Y_ANGLE);
	mlx_string_put(MLX, WIN, Y_SPACE, y - 1, NBR_YELLOW, tmp);
	free(tmp);
	tmp = TO_STR(Z_ANGLE);
	mlx_string_put(MLX, WIN, Z_SPACE, y - 1, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, ZOOM);
	tmp = TO_STR(SCALE);
	mlx_string_put(MLX, WIN, Z_SPACE, y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, Z_MUL);
	tmp = TO_STR(Z_VAL_MUL);
	mlx_string_put(MLX, WIN, Z_SPACE, y, NBR_YELLOW, tmp);
	free(tmp);
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
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_ISOMETRIC);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_TOP_VIEW);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_SIDE_VIEW);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_FRONT_VIEW);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_CONIC);
	mlx_string_put(MLX, WIN, X_START, NEXT_LINE(y), WHITE, STR_SPHERE);
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
