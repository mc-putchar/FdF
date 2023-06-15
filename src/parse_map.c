/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:39:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/15 13:21:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_values(t_map *map, char **split_line, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (split_line[j])
		++j;
	if (!map->width)
		map->width = j;
	else if (map->width != j && CHECK_ROWS)
		return (--(map->init), EXIT_FAILURE);
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

static ssize_t	get_file_size(int fd, int *line_count)
{
	ssize_t	size;
	ssize_t	r;
	char	buf[READ_BLOCK];
	int		i;

	size = 0;
	r = read(fd, buf, READ_BLOCK);
	while (r > 0)
	{
		size += r;
		i = 0;
		while (i < r)
			if (buf[i++] == '\n')
				(*line_count)++;
		r = read(fd, buf, READ_BLOCK);
	}
	if (r < 0)
		return (-1);
	if (fd > 2)
		close(fd);
	return (size);
}

static void	read_map(int fd, t_map *map)
{
	char	*line;
	char	**split_line;

	map->width = 0;
	map->z = malloc(sizeof(int *) * map->height);
	map->c = malloc(sizeof(int *) * map->height);
	if (!map->z || !map->c)
		error_handler(ENOMEM, NULL, &free_map, map);
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
			error_handler(ENOMEM, NULL, &free_map, map);
		if (get_values(map, split_line, (map->init)++) && \
			free_arr(split_line) && fgnl(fd))
			error_handler(EMAPINV, "Failed to read map", &free_map, map);
		(void)free_arr(split_line);
		line = get_next_line(fd);
	}
	if (fd > 2)
		close(fd);
}

static int	get_file_fd(char *path)
{
	if (!path)
		return (-1);
	if (path[0] == '-' && !path[1])
		return (0);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".fdf", 4))
		return (-1);
	return (open(path, O_RDONLY));
}

t_map	*parse_map(char *path)
{
	int		fd;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error_handler(ENOMEM, NULL, NULL, NULL);
	map->init = 0;
	map->height = 0;
	errno = 0;
	fd = get_file_fd(path);
	if (fd < 0)
		error_handler(errno, path, &free_map, map);
	if (get_file_size(fd, &map->height) < 0)
		error_handler(errno, path, &free_map, map);
	if (map->height == 0)
		error_handler(EINVAL, path, &free_map, map);
	map->path = path;
	fd = get_file_fd(path);
	if (fd < 0)
		error_handler(errno, path, &free_map, map);
	read_map(fd, map);
	if (normalize_colors(map))
		error_handler(ENOMEM, NULL, &free_map, map);
	return (map);
}
