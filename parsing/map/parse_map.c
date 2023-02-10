/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:17:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/01 18:02:40 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

static
char	*skip_spaces(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (s);
}

static
int	get_key(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

static
char	*get_path(char *s)
{
	return (skip_spaces(s));
}

int	parse_line(char *line, t_map *map)
{
	const char	*tmp;
	int			jump;

	line = skip_spaces(line);
	if (!*line)
		return (EXIT_SUCCESS);
	jump = get_key(line);
	tmp = line;
	if (set_key(map, ft_getnstr(line, jump)))
		return (EXIT_FAILURE);
	line = get_path(line + jump + 1);
	if (ft_strchr(line, ' '))
		return (ft_printf("{blue}Path Texture: {red}Failed{reset}\n"));
	return (set_texture(map, tmp, line));
}
