/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:55:04 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/10 02:42:26 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

static
int	set_map(t_map *map, const char *src_map)
{
	const char	*ptr;
	const char	*p;
	int			i;
	int			res;

	map -> map = ft_calloc(sizeof(char *), map -> height + 1);
	if (!map -> map)
		return (EXIT_FAILURE);
	i = 0;
	ptr = src_map;
	p = ptr;
	while (*ptr)
	{
		if (*ptr++ == '\n' || (!*ptr && i == map -> height - 1))
		{
			map -> map[i] = ft_strndup(p, ptr - p - (*ptr != 0));
			if (!map -> map[i])
				return (EXIT_FAILURE);
			if (ft_isspace(map -> map[i][ptr - p - (*ptr != 0) - 1])
				|| accept_char(map -> map[i], ptr - p - (*ptr != 0)))
				return (EXIT_FAILURE);
			p = ptr;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

static
int	readmap(t_map *map, int fd)
{
	static char	*tmp_map = 0;
	char		*line;
	size_t		size;
	size_t		x;
	size_t		y;

	size = 0;
	y = 0;
	x = 0;
	//while (1) {
	//	line = readfile(fd, false);
	//	if (!line) return (EXIT_FAILURE) ;
	//	if (*line == '\n')
	//		ft_memdel((void **)& line);
	//	else
	//		break ;
	//}
	while (1)
	{
		if (size > x)
			x = size;
		line = readfile(fd, false);
		if (!line)
			break ;
		if (!*line || *line == '\n')
		{
			ft_memdel((void **)& line);
			return (EXIT_FAILURE);
		}
		ft_realloc(& tmp_map, line);
		size = ft_strlen(line);
		ft_memdel((void **)& line);
		y++;
	}
	map -> height = y;
	map -> width = x;
	if (tmp_map)
	{
		if (set_map(map, tmp_map))
		{
			ft_memdel((void **)& tmp_map);
			return (EXIT_FAILURE);
		}
		ft_memdel((void **)& tmp_map);
	}
	return (EXIT_SUCCESS);
}

static
int	readinfos(t_map *map, int fd)
{
	char	*line;

	line = readfile(fd, true);
	while (line)
	{
		if (parse_line(line, map))
		{
			ft_memdel((void **)& line);
			return (ft_printf("{blue}Parse line: {red}Failed{reset}\n"));
		}
		if (textures_is_set(map))
		{
			ft_memdel((void **)& line);
			return (readmap(map, fd));
		}
		ft_memdel((void **)& line);
		line = readfile(fd, true);
	}
	ft_memdel((void **)& line);
	return (EXIT_SUCCESS);
}

static
int	check_extension(const char *filename)
{
	size_t	size;
	size_t	ext_size;

	size = ft_strlen(filename);
	ext_size = ft_strlen(EXTENSION);
	if (size >= 4)
		return (ft_strcmp((filename + size) - ext_size, EXTENSION));
	return (EXIT_FAILURE);
}

int	parse_map(t_map *map)
{
	int	fd;

	if (check_extension(map->filename))
		return (ft_printf("{blue}Extension: {red}Failed{reset}\n"));
	fd = open(map -> filename, O_RDONLY, 0644);
	if (fd == -1)
		return (ft_printf("{blue}Opening file: {red}Failed{reset}\n"));
	if (readinfos(map, fd))
	{
		close(fd);
		return (ft_printf("{blue}Read map: {red}Failed{reset}{reset}\n"));
	}
	close(fd);
	return (EXIT_SUCCESS);
}
