/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:20:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/27 04:12:50 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	set_key(t_map *map, const char *key)
{
	static const char	*c_key[KEY_SIZE] = {
		"SO", "NO", "WE", "EA", "F", "C"
	};
	bool				**b_key;
	bool				match;
	int					i;

	i = -1;
	b_key = (bool *[KEY_SIZE]){&map -> so_is_defined, & map -> no_is_defined, \
							& map -> we_is_defined, & map -> ea_is_defined, \
						& map -> floor_is_defined, & map -> ceil_is_defined};
	match = false;
	while (++i < KEY_SIZE)
	{
		if (ft_strcmp(key, c_key[i]) == 0)
		{
			if (*b_key[i] == true)
				return (ft_printf("{blue}Doublon: {red}%s{reset}\n", key));
			*b_key[i] = true;
			match = true;
		}
	}
	return (!match);
}

int	set_color(int (*rgb)[3], const char *color)
{
	int	tmp;
	int	i;

	i = 0;
	while (*color)
	{
		tmp = 0;
		while (ft_isdigit(*color))
		{
			tmp = (tmp * 10) + *color - '0';
			if (tmp > 255)
				return (EXIT_FAILURE);
			color++;
		}
		if (i != 2 && *color != ',')
			return (EXIT_FAILURE);
		color++;
		(*rgb)[i++] = tmp;
	}
	return (EXIT_SUCCESS);
}

int	set_texture(t_map *map, const char *key, const char *texture)
{
	const char	*c_key[4] = {
		"SO", "NO", "WE", "EA"
	};
	char		***b_key;
	int			i;

	i = -1;
	b_key = (char **[4]){& map->path_so, & map->path_no, \
							& map->path_we, & map->path_ea};
	if (ft_strcmp(key, "F") == 0)
		return (set_color(& map -> color_floor, texture));
	if (ft_strcmp(key, "C") == 0)
		return (set_color(& map -> color_ceil, texture));
	while (++i < 4)
	{
		if (ft_strcmp(key, c_key[i]) == 0)
			*b_key[i] = ft_strndup(texture, ft_strlen(texture) - 1);
	}
	return (EXIT_SUCCESS);
}
