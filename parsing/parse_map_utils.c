/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:50:37 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/12 18:23:11 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

char	*readfile(int fd, bool force)
{
	int		ret;
	char	*c;
	char	*line;

	line = 0;
	ret = 1;
	c = (char [2]){0, 0};
	while (ret)
	{
		ret = read(fd, & c[0], 1);
		if (ret == -1)
			return (0);
		if (ret == 0 && line)
			return (line);
		if (ret == 0 && !line)
			break ;
		ft_realloc(& line, c);
		if (!line)
			return (NULL);
		if (line[0] == '\n' && force)
			ft_memdel((void **)& line);
		else if (c[0] == '\n')
			return (line);
	}
	ft_memdel((void **)& line);
	return (NULL);
}

int	textures_is_set(t_map *map)
{
	return (map -> so_is_defined && map -> no_is_defined
		&& map -> we_is_defined && map -> ea_is_defined
		&& map -> floor_is_defined && map -> ceil_is_defined);
}

int	accept_char(const char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && (s[i] == '0' || s[i] == '1' || s[i] == 'N'
		|| s[i] == 'S' || s[i] == 'E' || s[i] == 'W'
		|| s[i] == ' ' || s[i] == 'H' || s[i] == 'D'))
		i++;
	return (s[i] != '\0');
}
