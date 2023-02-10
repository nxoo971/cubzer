/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:25:06 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/08 03:25:51 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	move_vertical(t_data *data, int add)
{
	const int	y = data -> player.y;
	const int	x = data -> player.x;

	if (y > 0 && data -> map.map[y + add][x] != WALL)
	{
		data -> player.y += add;
		data -> map.map[y + add][x] = 'N';
		data -> map.map[y][x] = BLANK;
	}
}

void	move_horizontal(t_data *data, int add)
{
	const int	y = data -> player.y;
	const int	x = data -> player.x;

	if (y > 0 && data -> map.map[y][x + add] != WALL)
	{
		data -> player.x += add;
		data -> map.map[y][x + add] = 'N';
		data -> map.map[y][x] = BLANK;
	}
}
