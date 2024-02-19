/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:25:38 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/18 18:57:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_vars *fdf)
{
	fdf->map[fdf->in_use].angles[X] = 30;
	fdf->map[fdf->in_use].angles[Y] = 330;
	fdf->map[fdf->in_use].angles[Z] = 45;
}

void	top_view(t_vars *fdf)
{
	fdf->map[fdf->in_use].angles[X] = 0;
	fdf->map[fdf->in_use].angles[Y] = 0;
	fdf->map[fdf->in_use].angles[Z] = 0;
}

void	front_view(t_vars *fdf)
{
	fdf->map[fdf->in_use].angles[X] = 90;
	fdf->map[fdf->in_use].angles[Y] = 0;
	fdf->map[fdf->in_use].angles[Z] = 0;
}

void	side_view(t_vars *fdf)
{
	fdf->map[fdf->in_use].angles[X] = 90;
	fdf->map[fdf->in_use].angles[Y] = 90;
	fdf->map[fdf->in_use].angles[Z] = 0;
}

void	choose_projection(t_vars *fdf, int prespective)
{
	if (prespective == ISOMETRIC)
	{
		isometric(fdf);
		fdf->map[fdf->in_use].spherical = 0;
		fdf->map[fdf->in_use].conic = 0;
	}
	if (prespective == TOP_VIEW)
		top_view(fdf);
	if (prespective == SIDE_VIEW)
		side_view(fdf);
	if (prespective == FRONT_VIEW)
		front_view(fdf);
	if (prespective == CONIC)
	{
		isometric(fdf);
		fdf->map[fdf->in_use].conic = !fdf->map[fdf->in_use].conic;
		fdf->map[fdf->in_use].spherical = 0;
	}
	if (prespective == SPHERE)
	{
		isometric(fdf);
		fdf->map[fdf->in_use].spherical = !fdf->map[fdf->in_use].spherical;
		fdf->map[fdf->in_use].conic = 0;
	}
}
