/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prespectives.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:25:38 by jcameira          #+#    #+#             */
/*   Updated: 2024/01/25 12:24:10 by jcameira         ###   ########.fr       */
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
	if (prespective == 0)
		isometric(fdf);
	if (prespective == 1)
		top_view(fdf);
	if (prespective == 2)
		front_view(fdf);
	if (prespective == 3)
		side_view(fdf);
}