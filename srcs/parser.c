/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:30:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/13 01:49:02 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_polar_coordinates(t_map *map)
{
	int		x;
	int		y;
	float	steps_x;
	float	steps_y;

	steps_x = (M_PI * 2) / (map->limits[X] - 1);
	steps_y = M_PI / (map->limits[Y]);
	map->radius = (map->limits[X] * map->scale) / (M_PI * 2);
	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			map->points[y][x].polar[LONGITUDE] = -(map->points[y][x].coordinates[X]) * steps_x;
			map->points[y][x].polar[LATITUDE] = ((map->points[y][x].coordinates[Y]) + (map->limits[Y] / 2)) * steps_y;
		}
	}
}

void	update_z_limits(t_map *map, t_point **points)
{
	int	y;
	int	x;

	y = -1;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
		{
			if (map->z_min > round(points[y][x].coordinates[Z]))
				map->z_min = round(points[y][x].coordinates[Z]);
			if (map->z_max < round(points[y][x].coordinates[Z]))
				map->z_max = round(points[y][x].coordinates[Z]);
		}
	}
	map->z_range = map->z_max - map->z_min;
}

void	load_coordinates(t_map *map, t_point ***points, char **z_values, int y)
{
	int	x;

	x = -1;
	while (++x < map->limits[X])
	{
		(*points)[y][x].coordinates[X] = (x - (map->limits[X] / 2) + 0.5);
		(*points)[y][x].coordinates[Y] = (y - (map->limits[Y] / 2) + 0.5);
		(*points)[y][x].coordinates[Z] = (float)atoi(z_values[x]);
	}
}

t_point	**get_original_points(t_map *map)
{
	int		y;
	char	**z_values;
	t_point	**points;

	points = malloc(sizeof (t_point *) * map->limits[Y]);
	if (!points)
		return (NULL);
	y = -1;
	while (++y < map->limits[Y])
	{
		points[y] = malloc(sizeof (t_point) * map->limits[X]);
		if (!points[y])
			return (NULL);
		z_values = ft_split(map->map_info[y], ' ');
		if (!z_values)
			return (NULL);
		load_coordinates(map, &points, z_values, y);
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

	map_info = malloc(sizeof (char *) * map->limits[Y]);
	if (!map_info)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = get_next_line(fd);
	y = -1;
	while (++y < map->limits[Y])
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
	map->limits[X] = (float)word_count(trimmed_line, ' ');
	map->limits[Y] = 0;
	free(trimmed_line);
	while (line)
	{
		map->limits[Y]++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("X limit: %d\n", map->limits[X]);
	printf("Y limit: %d\n", map->limits[Y]);
	close(fd);
}

void	find_best_z_multiplier(t_map *map)
{
	int	x;
	int	y;
	int	tmp_range;

	tmp_range = map->z_range;
	while ((float)tmp_range / (float)map->limits[X] > 0.2)
	{
		map->z_multiplier -= 0.1;
		tmp_range = map->z_multiplier * (map->z_max - map->z_min);
	}
	while ((float)tmp_range / (float)map->limits[X] < 0.2)
	{
		map->z_multiplier += 0.1;
		tmp_range = map->z_multiplier * (map->z_max - map->z_min);
	}
	y = -1;
	while (++y < map->limits[Y])
	{
		x = -1;
		while (++x < map->limits[X])
			map->points[y][x].coordinates[Z] *= map->z_multiplier;
	}
	update_z_limits(map, map->points);
}

void	parser(t_map *map, char *file)
{
	map_init(map);
	get_x_y_limits(map, file);
	map->map_info = read_map(map, file);
	map->points = get_original_points(map);
	update_z_limits(map, map->points);
	find_best_z_multiplier(map);
	//printf("Zmax and Zmin: %d %d\n", map->z_max, map->z_min);
	set_point_color(map);
	get_polar_coordinates(map);
	//printf("Z_min, Z_max: %d, %d\n", map->z_min, map->z_max);
}
