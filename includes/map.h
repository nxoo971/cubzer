/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:12:14 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/18 05:58:41 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

# define EXTENSION	".cub"
# define BLOC_SIZE	16
# define KEY_SIZE	6

# define WALL	'1'
# define BLANK	'0'
# define PERSO	'N'

typedef struct s_map
{
//	filename
	const char	*filename;

//	window size
	int			height;
	int			width;

//	textures
	bool		no_is_defined;
	char		*path_no;

	bool		so_is_defined;
	char		*path_so;

	bool		we_is_defined;
	char		*path_we;

	bool		ea_is_defined;
	char		*path_ea;

	bool		floor_is_defined;
	int			color_floor[3];

	bool		ceil_is_defined;
	int			color_ceil[3];

//	map
	char		**map;
}	t_map;

typedef struct s_player	t_player;

/*
	DIRECTORY: ./parsing/
//	parse.c
*/

/*
	DIRECTORY: ./parsing/map
*/
//	parse_map.c
int		parse_line(char *line, t_map *map);
//	parse_map_utils.c
char	*readfile(int fd, bool force);
int		textures_is_set(t_map *map);
int		accept_char(const char *s, size_t len);
//	set_infos.c
int		set_key(t_map *map, const char *key);
int		set_texture(t_map *map, const char *key, const char *texture);
//	valid_map.c
int		parse_map(t_map *map, t_player *player);

#endif
