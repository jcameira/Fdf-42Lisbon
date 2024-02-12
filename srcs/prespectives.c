/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prespectives.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:25:38 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/12 18:43:44 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_vars *fdf)
{
	fdf->map.angles[X] = 30;
	fdf->map.angles[Y] = 330;
	fdf->map.angles[Z] = 45;
}

void	top_view(t_vars *fdf)
{
	fdf->map.angles[X] = 0;
	fdf->map.angles[Y] = 0;
	fdf->map.angles[Z] = 0;
}

void	front_view(t_vars *fdf)
{
	fdf->map.angles[X] = 90;
	fdf->map.angles[Y] = 0;
	fdf->map.angles[Z] = 0;
}

void	side_view(t_vars *fdf)
{
	fdf->map.angles[X] = 90;
	fdf->map.angles[Y] = 90;
	fdf->map.angles[Z] = 0;
}

void	choose_prespective(t_vars *fdf, int prespective)
{
	if (prespective == ISOMETRIC)
		isometric(fdf);
	if (prespective == TOP_VIEW)
		top_view(fdf);
	if (prespective == SIDE_VIEW)
		side_view(fdf);
	if (prespective == FRONT_VIEW)
		front_view(fdf);
}