/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/17 16:47:45 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_polar_coord(t_map *map)
{
	int		x;
	int		y;
	float	steps_x;
	float	steps_y;

	steps_x = (M_PI * 2) / (map->lim[X] - 1);
	steps_y = M_PI / (map->lim[Y]);
	map->radius = (map->lim[X] * map->scale) / (M_PI * 2);
	y = -1;
	while (++y < map->lim[Y])
	{
		x = -1;
		while (++x < map->lim[X])
		{
			map->points[y][x].polar[LONGITUDE] = -(map->points[y][x].coord[X])
				* steps_x;
			map->points[y][x].polar[LATITUDE] = ((map->points[y][x].coord[Y])
					+ (map->lim[Y] / 2)) * steps_y;
		}
	}
}

void	update_z_ranges(t_map *map)
{
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
			if (map->z_min > round(points[y][x].coord[Z]))
				map->z_min = round(points[y][x].coord[Z]);
			if (map->z_max < round(points[y][x].coord[Z]))
				map->z_max = round(points[y][x].coord[Z]);
		}
	}
	map->z_range = map->z_max - map->z_min;
	update_z_ranges(map);
}

void	load_coord(t_map *map, t_point ***points, char **z_values, int y)
{
	int		x;
	char	**z_info;

	x = -1;
	while (++x < map->lim[X])
	{
		(*points)[y][x].coord[X] = (x - (map->lim[X] / 2) + 0.5);
		(*points)[y][x].coord[Y] = (y - (map->lim[Y] / 2) + 0.5);
		(*points)[y][x].coord[Z] = (float)atoi(z_values[x]);
		if (ft_strchr(z_values[x], ','))
		{
			z_info = ft_split(z_values[x], ',');
			(*points)[y][x].original_color = ft_strhextol(z_info[1] + 2);
			free_split(z_info);
		}
		else
			(*points)[y][x].original_color = WHITE;
		(*points)[y][x].color = (*points)[y][x].original_color;
	}
}

t_point	**get_original_points(t_map *map)
{
	int		y;
	char	**z_values;
	t_point	**points;

	points = malloc(sizeof (t_point *) * map->lim[Y]);
	if (!points)
		return (NULL);
	y = -1;
	while (++y < map->lim[Y])
	{
		points[y] = malloc(sizeof (t_point) * map->lim[X]);
		if (!points[y])
			return (NULL);
		z_values = ft_split(map->map_info[y], ' ');
		if (!z_values)
			return (NULL);
		load_coord(map, &points, z_values, y);
		free_split(z_values);
	}
	return (points);
}

char	**read_map(t_map *map, char *file)
{
	int		fd;
	int		y;
	char	**map_info;
	char	*tmp;

	map_info = malloc(sizeof (char *) * map->lim[Y]);
	if (!map_info)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = get_next_line(fd);
	y = -1;
	while (++y < map->lim[Y])
	{
		map_info[y] = ft_strtrim(tmp, " \n");
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	return (map_info);
}

void	get_x_y_limits(t_map *map, char *file)
{
	int		fd;
	char	*line;
	char	*trimmed_line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	trimmed_line = ft_strtrim(line, " \n");
	map->lim[X] = (float)word_count(trimmed_line, ' ');
	map->lim[Y] = 0;
	free(trimmed_line);
	while (line)
	{
		map->lim[Y]++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	find_best_z_mul(t_map *map)
{
	int	x;
	int	y;
	int	tmp_range;

	tmp_range = map->z_range;
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

void	parser(t_map *map, char *file)
{
	map_init(map, file);
	get_x_y_limits(map, file);
	map->map_info = read_map(map, file);
	map->points = get_original_points(map);
	update_z_limits(map, map->points);
	find_best_z_mul(map);
	get_polar_coord(map);
}
