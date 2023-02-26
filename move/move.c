/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:25:06 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/26 01:30:51 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	move_player(t_data *data, const int sign_y, const int sign_x)
{
	const double	x = data -> player.x;
	const double	y = data -> player.y;
	const double	move_y = (data -> params.dir_y * MOVE_SPEED) * sign_y;
	const double	move_x = (data -> params.dir_x * MOVE_SPEED) * sign_x;

	if (data -> map.map[(int)y][(int)(x + move_x)] != WALL)
	{
		data -> player.x = x + move_x;
		data->player.x_mini = x + move_x;
	}
	if (data -> map.map[(int)(y + move_y)][(int)x] != WALL)
	{
		data -> player.y = y + move_y;
		data->player.y_mini = y + move_y;
	}
}

void	move_player_side(t_data *data, const int sign_y, const int sign_x)
{
	const double	x = data -> player.x;
	const double	y = data -> player.y;
	const double	move_y = (data -> params.dir_y * MOVE_SPEED) * sign_y;
	const double	move_x = (data -> params.dir_x * MOVE_SPEED) * sign_x;

	if (data -> map.map[(int)y][(int)(x + move_y)] != WALL)
		data -> player.x = x + move_y;
	if (data -> map.map[(int)(y + move_x)][(int)x] != WALL)
		data -> player.y = y + move_x;
}

void	move_angle(t_data *data, const int sign)
{
	const double		oldir = data -> params.dir_x;
	const double		old_plane = data -> params.plane_x;
	const double		rotation_cos = cos(ROTATION_SPEED * sign);
	const double		rotation_sin = sin(ROTATION_SPEED * sign);
	t_params			*params;

	params = & data -> params;
	params -> dir_x = params -> dir_x * rotation_cos - params -> dir_y * rotation_sin;
	params -> dir_y = oldir * rotation_sin + params -> dir_y * rotation_cos;
	params -> plane_x = params -> plane_x * rotation_cos - params -> plane_y * rotation_sin;
	params -> plane_y = old_plane * rotation_sin + params -> plane_y * rotation_cos;
}
