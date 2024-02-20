/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:23:16 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/20 11:50:47 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	early_lim_exit(char *line, char *trimmed_line, int fd, char *file)
{
	ft_printf(ERROR_INV_MAP, file);
	if (line)
		free(line);
	if (trimmed_line)
		free(trimmed_line);
	close(fd);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		while (split[++i])
			free(split[i]);
		free(split);
	}
}

void	free_map(t_map *map)
{
	int	y;

	y = -1;
	while (++y < map->lim[Y])
	{
		free(map->points[y]);
		free(map->map_info[y]);
	}
	free(map->points);
	free(map->map_info);
}

void	free_proj(t_point **proj, int y_lim)
{
	int	y;

	if (proj)
	{
		y = -1;
		while (++y < y_lim)
			free(proj[y]);
		free(proj);
	}
}

int	end_program(t_vars *fdf, int maps, int no_vars)
{
	int	i;

	i = -1;
	while (++i < maps)
		free_map(&fdf->map[i]);
	free(fdf->map);
	if (!no_vars)
	{
		mlx_destroy_image(fdf->mlx, fdf->bitmap.img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	exit(0);
}
