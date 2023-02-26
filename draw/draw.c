/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:28:27 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/26 22:05:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	draw_bloc(t_mlx mlx, const int y, const int x, const int color)
{
	int	h;
	int	w;

	h = -1;
	while (++h < BLOC_SIZE)
	{
		w = -1;
		while (++w < BLOC_SIZE)
			mlx_put_pixel(mlx, h + (y * BLOC_SIZE), w + (x * BLOC_SIZE), color);
	}
}

void	draw_game(t_data *data)
{
	const int	mid = HEIGHT / 2;
	int			*colors;
	int			y;
	int			x;

	colors = (int [2]){set_rgb(data -> map.color_ceil),
		set_rgb(data -> map.color_floor)};
	data -> mlx.img = data -> img;
	data -> mlx.addr = data -> addr;
	data -> mlx.index = MLX_IMG_MAP;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(data -> mlx, y, x, colors[y >= mid]);
	}
}
