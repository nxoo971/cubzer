/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 00:00:23 by rferradi          #+#    #+#             */
/*   Updated: 2023/02/27 00:01:53 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_square(t_data *data, double x, double y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PIXEL)
	{
		j = -1;
		while (++j < PIXEL)
			data->buf[(int)y * PIXEL + i][(int)x * PIXEL + j] = color;
	}
}

void	mini_map(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = OFFSET - 1;
	y = ceil(data->player.y - LENMAP / 2);
	while (++i < LENMAP)
	{
		x = ceil(data->player.x - LENMAP / 2);
		j = OFFSET - 1;
		while (++j < LENMAP)
		{
			if (x >= 0 && y >= 0 && data->map.map[y][x] == WALL)
				draw_square(data, i, j, 0x00FFFFFF);
			else if (x == (int)data->player.x && y == (int)data->player.y)
				draw_square(data, i, j, 0x00FF0000);
			else
				draw_square(data, i, j, 0x00000000);
			x++;
		}
		y++;		
	}
}
