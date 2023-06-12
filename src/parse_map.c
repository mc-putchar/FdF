/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:39:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 22:36:47 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_map(t_map *map)
{
	int	i;

	if (!map)
		return (EXIT_SUCCESS);
	i = 0;
	if (map->z && map->z[i])
	{
		while (i < map->height && map->z[i])
		{
			free(map->z[i]);
			free(map->c[i++]);
		}
	}
	free(map->z);
	free(map->c);
	free(map);
	return (EXIT_SUCCESS);
}

int	get_values(t_map *map, char **split_line, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (split_line[j])
		++j;
	if (!map->width)
		map->width = j;
	else if (map->width != j)
		return (EXIT_FAILURE);
	map->z[i] = malloc(sizeof(int) * j);
	map->c[i] = malloc(sizeof(int) * j);
	if (!map->z[i] || !map->c[i])
		return (EXIT_FAILURE);
	j = -1;
	while (split_line[++j])
	{
		tmp = ft_strchr(split_line[j], ',');
		if (tmp)
			map->c[i][j] = ft_atoi_base(tmp + 3, HEX_BASE);
		else
			map->c[i][j] = 0x00FFFFFF;
		map->z[i][j] = ft_atoi(split_line[j]);
	}
	return (EXIT_SUCCESS);
}

int	convert_map(char *str, t_map *map)
{
	char	**split_line;
	char	**split_str;
	int		i;

	map->z = malloc(sizeof(int *) * map->height);
	map->c = malloc(sizeof(int *) * map->height);
	if (!map->z || !map->c)
		return (EXIT_FAILURE);
	split_str = ft_split(str, '\n');
	free(str);
	if (!split_str)
		return (EXIT_FAILURE);
	i = 0;
	while (split_str[i])
	{
		split_line = ft_split(split_str[i], ' ');
		if (!split_line)
			return (free_arr(split_str), EXIT_FAILURE);
		if (get_values(map, split_line, i))
			return (free_arr(split_str), free_arr(split_line), EXIT_FAILURE);
		free_arr(split_line);
		i++;
	}
	free_arr(split_str);
	return (EXIT_SUCCESS);
}

void	read_map(int fd, t_map *map)
{
	char	*line;
	char	*map_str;
	char	*tmp;

	map->height = 0;
	map->width = 0;
	map_str = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(map_str, line);
		free(map_str);
		if (!tmp)
			error_handler(ENOMEM, NULL, &free_map, map);
		free(line);
		map_str = tmp;
		line = get_next_line(fd);
		map->height++;
	}
	if (map->height == 0)
		error_handler(EINVAL, NULL, &free_map, map);
	if (fd > 2)
		close(fd);
	if (convert_map(map_str, map))
		error_handler(ENOMEM, NULL, &free_map, map);
}

int	parse_map(char *path, t_fdf *fdf)
{
	int		fd;
	t_map	*map;

	if (!path)
		error_handler(EINVAL, NULL, NULL, NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		error_handler(errno, NULL, NULL, NULL);
	if (path[0] == '-' && !path[1])
		fd = 0;
	else
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".fdf", 4))
			error_handler(EINVAL, path, &free_map, map);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			error_handler(errno, path, &free_map, map);
	}
	read_map(fd, map);
	fdf->map = map;
	return (EXIT_SUCCESS);
}
