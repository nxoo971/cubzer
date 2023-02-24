/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:28:27 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 19:18:31 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	draw_bloc(t_mlx mlx, const int y, const int x, const int color)
{
	for (int h = 0; h < BLOC_SIZE; h++)
		for (int w = 0; w < BLOC_SIZE; w++)
			mlx_put_pixel(mlx, h + (y * BLOC_SIZE), w + (x * BLOC_SIZE), color);
}

void	draw_game(t_data *data)
{
	const int	mid = HEIGHT / 2;
	int			*colors;

	colors = (int [2]){set_rgb(data -> map.color_ceil), set_rgb(data -> map.color_floor)};
	data -> mlx.img = data -> img;
	data -> mlx.addr = data -> addr;
	data -> mlx.index = MLX_IMG_MAP;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			mlx_put_pixel(data -> mlx, y, x, colors[y >= mid]);
}
