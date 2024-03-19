/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:25:20 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/19 17:35:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	update_z_ranges(t_map *map)
{
	map->z_range = map->z_max - map->z_min;
	if (map->z_max > 0 && map->z_min < 0)
	{
		map->z_pos_range = map->z_max;
		map->z_neg_range = -map->z_min;
	}
	else if (map->z_max > 0 && map->z_min >= 0)
	{
		map->z_pos_range = map->z_range;
		map->z_neg_range = 0;
	}
	else if (map->z_max <= 0 && map->z_min < 0)
	{
		map->z_pos_range = 0;
		map->z_neg_range = map->z_range;
	}
}

void	update_z_limits(t_map *map, t_point **points)
{
	int	y;
	int	x;

	y = -1;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
		{
			if (map->z_min > ft_round(points[y][x].coord[Z]))
				map->z_min = ft_round(points[y][x].coord[Z]);
			if (map->z_max < ft_round(points[y][x].coord[Z]))
				map->z_max = ft_round(points[y][x].coord[Z]);
		}
	}
	update_z_ranges(map);
}

int	get_x_y_limits(t_map *map, char *file)
{
	int		fd;
	char	*line;
	char	*trimmed_line;

	if (fd_check(&fd, file))
		return (1);
	line = get_next_line(fd);
	trimmed_line = ft_strtrim(line, " \n");
	if (!trimmed_line)
		return (early_lim_exit(line, trimmed_line, fd, file));
	map->lim[X] = (float)word_count(trimmed_line, ' ');
	while (line)
	{
		map->lim[Y]++;
		free(line);
		free(trimmed_line);
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed_line = ft_strtrim(line, " \n");
		if (!trimmed_line || word_count(trimmed_line, ' ') != map->lim[X])
			return (early_lim_exit(line, trimmed_line, fd, file));
	}
	close(fd);
	return (0);
}

void	find_best_z_mul(t_map *map)
{
	int	x;
	int	y;
	int	tmp_range;

	tmp_range = map->z_range;
	if (tmp_range == 0)
		return ;
	while ((float)tmp_range / (float)map->lim[X] > 0.05)
	{
		map->mul[Z] -= 0.1;
		tmp_range = map->mul[Z] * (map->z_max - map->z_min);
	}
	while ((float)tmp_range / (float)map->lim[X] < 0.05)
	{
		map->mul[Z] += 0.1;
		tmp_range = map->mul[Z] * (map->z_max - map->z_min);
	}
	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
			map->points[y][x].coord[Z] *= map->mul[Z];
	}
	update_z_limits(map, map->points);
}
