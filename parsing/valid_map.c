/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:55:04 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 19:18:20 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
int	set_map(t_map *map, t_player *player, const char *src_map)
{
	const char	*ptr;
	const char	*p;
	bool		player_exist;
	int			pos_x;
	int			size;
	int			i;

	map -> map = ft_calloc(sizeof(char *), map -> height + 1);
	if (!map -> map)
		return (EXIT_FAILURE);
	i = 0;
	ptr = src_map;
	p = ptr;
	player_exist = false;
	while (*ptr)
	{
		if (*ptr++ == '\n' || (!*ptr && i == map -> height - 1))
		{
			size = ptr - p - (*ptr != 0);
			pos_x = ft_is_in_string(p, "NSEW", size);
			if (pos_x > -1)
			{
				if (player_exist)
					return (ft_printf("{blue}set_map: {red}FAILED{reset} -- {bgred}player doublon: [%c|%c]{reset}\n",
							map -> map[(int)player -> y][(int)player -> x], p[pos_x]));
				player -> y = i + 0.5;
				player -> x = pos_x + 0.5;
				player_exist = true;
			}
			map -> map[i] = ft_strndup(p, size);
			if (!map -> map[i])
				return (EXIT_FAILURE);
			if (ft_isspace(map -> map[i][size - 1])
				|| accept_char(map -> map[i], size))
				return (ft_printf("{blue}set_map: {red}FAILED -- wrong chars{reset}\n"));
			p = ptr;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

static
int	readmap(t_map *map, t_player *player, int fd)
{
	static char	*tmp_map = 0;
	char		*line;
	size_t		size;
	size_t		x;
	size_t		y;

	size = 0;
	y = 0;
	x = 0;
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
		if (set_map(map, player, tmp_map))
		{
			ft_memdel((void **)& tmp_map);
			return (EXIT_FAILURE);
		}
		ft_memdel((void **)& tmp_map);
	}
	return (EXIT_SUCCESS);
}

static
int	readinfos(t_map *map, t_player *player, int fd)
{
	char	*line;

	line = readfile(fd, true);
	while (line)
	{
		if (parse_line(line, map))
		{
			ft_memdel((void **)& line);
			return (ft_printf("{blue}parse line: {red}FAILED{reset}\n"));
		}
		if (textures_is_set(map))
		{
			ft_memdel((void **)& line);
			return (readmap(map, player, fd));
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

int	parse_map(t_map *map, t_player *player)
{
	int	fd;

	if (check_extension(map->filename))
		return (ft_printf("{blue}Extension: {red}FAILED{reset}\n"));
	fd = open(map -> filename, O_RDONLY, 0644);
	if (fd == -1)
		return (ft_printf("{blue}Opening file: {red}FAILED{reset}\n"));
	if (readinfos(map, player, fd))
	{
		close(fd);
		return (ft_printf("{blue}read map: {red}FAILED{reset}{reset}\n"));
	}
	close(fd);
	return (EXIT_SUCCESS);
}
