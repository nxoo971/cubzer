/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:25:06 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/20 09:09:57 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	move_player(t_data *data, const int sign_y, const int sign_x)
{
	const double	x = data -> player.x;
	const double	y = data -> player.y;
	const double	move_y = (data -> player.dir_y * MOVE_SPEED) * sign_y;
	const double	move_x = (data -> player.dir_x * MOVE_SPEED) * sign_x;

	if (data -> map.map[(int)y][(int)(x + move_x)] != WALL)
		data -> player.x = x + move_x;
	if (data -> map.map[(int)(y + move_y)][(int)x] != WALL)
		data -> player.y = y + move_y;
}

void	move_angle(t_data *data, const int sign)
{
	const double		oldir = data -> player.dir_x;
	const double		old_plane = data -> player.plane_x;
	const double		rotation_cos = cos(ROTATION_SPEED * sign);
	const double		rotation_sin = sin(ROTATION_SPEED * sign);
	t_player			*p;

	p = & data -> player;
	p -> dir_x = p -> dir_x * rotation_cos - p -> dir_y * rotation_sin;
	p -> dir_y = oldir * rotation_sin + p -> dir_y * rotation_cos;
	p -> plane_x = p -> plane_x * rotation_cos - p -> plane_y * rotation_sin;
	p -> plane_y = old_plane * rotation_sin + p -> plane_y * rotation_cos;
}
