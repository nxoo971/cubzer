/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:33:12 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/14 23:22:36 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
int	set_playerpos(t_player *p, const int y, const int x, const char c)
{
	static bool	exist = false;

	if (c == NORTH || c == WEST || c == EAST || c == SOUTH)
	{
		if (exist)
			return (ft_printf(\
	"{blue}set_map: {red} FAILED{reset} -- {bgred}player doublon{reset}\n"));
		exist = true;
		p -> y = y + .5;
		p -> x = x + .5;
		p -> p = c;
	}
	return (EXIT_SUCCESS);
}

static
int	set_map(t_map *map, t_player *player, const char *src_map)
{
	char	*tmp;
	int		i;
	int		j;

	map -> map = ft_split(src_map, '\n');
	if (!map -> map)
		return (EXIT_FAILURE);
	i = 0;
	while (map -> map[i])
	{
		tmp = map -> map[i];
		j = 0;
		while (tmp[j])
		{
			if (set_playerpos(player, i, j, tmp[j]))
				return (EXIT_FAILURE);
			j++;
		}
		if (ft_isspace(map -> map[i][j - 1]) || accept_char(map -> map[i], j))
			return (ft_printf(\
					"{blue}set_map: {red}FAILED -- wrong chars{reset}\n"));
		i++;
	}
	map->y = i;
	return (EXIT_SUCCESS);
}

static
int	doo(t_map *map, t_player *player, char *tmp_map, const int xy[2])
{
	map -> height = xy[0];
	map -> width = xy[1];
	if (tmp_map)
	{
		if (set_map(map, player, tmp_map))
		{
			ft_memdel((void **)& tmp_map);
			return (EXIT_FAILURE);
		}
		ft_memdel((void **)& tmp_map);
	}
	if (player -> y != -1 && player -> x != -1)
		return (EXIT_SUCCESS);
	return (ft_printf(\
	"{blue}set_map: {red}FAILED{reset} -- {bgred}player not found{reset}\n"));
}

int	stock_map(t_map *map, t_player *player, const int fd, char *tmp_map)
{
	char	*ptr;
	int		size;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (1)
	{
		ptr = readfile(fd, false);
		if (!ptr)
			break ;
		size = (int)ft_strlen(ptr);
		if (size > x)
			x = size;
		ft_realloc(& tmp_map, ptr);
		ft_memdel((void **)& ptr);
		y++;
	}
	return (doo(map, player, tmp_map, (int [2]){y, x}));
}
