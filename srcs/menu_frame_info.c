/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_frame_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 01:19:14 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/19 01:19:43 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_velocities(t_vars *fdf, int *y)
{
	char	*tmp;

	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		STR_TRANSLATION_VEL);
	tmp = ft_ftoa(fdf->map[fdf->in_use].t_vel, 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(STR_TRANSLATION_VEL), *y,
		NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		STR_ROTATION_VEL);
	tmp = ft_ftoa(fdf->map[fdf->in_use].r_vel, 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(STR_ROTATION_VEL), *y,
		NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE,
		STR_SCALE_VEL);
	tmp = ft_ftoa(fdf->map[fdf->in_use].s_vel, 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(STR_SCALE_VEL), *y,
		NBR_YELLOW, tmp);
	free(tmp);
}

void	put_zoom(t_vars *fdf, int *y)
{
	char	*tmp;

	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, ZOOM);
	tmp = ft_ftoa(fdf->map[fdf->in_use].scale, 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(ZOOM), *y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, X_MUL);
	tmp = ft_ftoa(fdf->map[fdf->in_use].mul[X], 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(X_MUL), *y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, Y_MUL);
	tmp = ft_ftoa(fdf->map[fdf->in_use].mul[Y], 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(Y_MUL), *y, NBR_YELLOW, tmp);
	free(tmp);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, Z_MUL);
	tmp = ft_ftoa(fdf->map[fdf->in_use].mul[Z], 1);
	mlx_string_put(fdf->mlx, fdf->win, x_end(Z_MUL), *y, NBR_YELLOW, tmp);
	free(tmp);
}

void	put_angles(t_vars *fdf, int *y)
{
	char	*tmp;

	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y), WHITE, DETAILS);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y) + 3,
		WHITE, ANGLES);
	mlx_string_put(fdf->mlx, fdf->win, X_START, next_line(y) - 4,
		WHITE, SPACES);
	tmp = ft_itoa(fdf->map[fdf->in_use].angles[X]);
	mlx_string_put(fdf->mlx, fdf->win, x_end(X_SPACE), *y - 5, NBR_YELLOW, tmp);
	free(tmp);
	tmp = ft_itoa(fdf->map[fdf->in_use].angles[Y]);
	mlx_string_put(fdf->mlx, fdf->win, x_end(Y_SPACE), *y - 5, NBR_YELLOW, tmp);
	free(tmp);
	tmp = ft_itoa(fdf->map[fdf->in_use].angles[Z]);
	mlx_string_put(fdf->mlx, fdf->win, x_end(Z_SPACE), *y - 5, NBR_YELLOW, tmp);
	free(tmp);
}
