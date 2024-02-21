/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:51:53 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/21 02:01:29 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	next_try(t_vars *fdf, t_point **proj)
{
	fdf->map[fdf->in_use].scale += 0.1;
	update_scale_dependants(&fdf->map[fdf->in_use], 0.1, 0);
	free_proj(proj, fdf->map[fdf->in_use].lim[Y]);
}

void	fit_window(t_vars *fdf)
{
	t_point	**proj;
	int		x;
	int		y;

	while (1)
	{
		proj = copy_map(fdf->map[fdf->in_use]);
		if (!proj)
			end_program(fdf, fdf->number_of_maps, 0);
		y = -1;
		while (++y < fdf->map[fdf->in_use].lim[Y])
		{
			x = -1;
			while (++x < fdf->map[fdf->in_use].lim[X])
			{
				if (!inside_window(fdf, proj[y][x]))
				{
					fdf->map[fdf->in_use].f_scale = fdf->map[fdf->in_use].scale;
					free_proj(proj, fdf->map[fdf->in_use].lim[Y]);
					return ;
				}
			}
		}
		next_try(fdf, proj);
	}
}
