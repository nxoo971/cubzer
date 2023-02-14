/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:28:27 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/14 03:27:39 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	draw_bloc(t_mlx mlx, const int y, const int x, const int color)
{
	for (int h = 0; h < BLOC_SIZE; h++)
		for (int w = 0; w < BLOC_SIZE; w++)
			mlx_put_pixel(mlx, w + (x * BLOC_SIZE), h + (y * BLOC_SIZE), color);
}

void	draw_minimap(t_data *data)
{
	static const int	colors[2] = {0x17B39B, 0xDB0FFF};
	const int			height = data -> map.height;
	const int			width = data -> map.width;
	char				**map;

	map = data -> map.map;
	data -> mlx.img = data -> img_map;
	data -> mlx.addr = data -> map_addr;
	data -> mlx.index = MLX_IMG_MINIMAP;
	for (int y = 0; y < height; y++)
		for (int x = 0; map[y][x]; x++)
				draw_bloc(data -> mlx, y, x, colors[map[y][x] == WALL]);
	draw_bloc(data -> mlx, data -> player.y, data -> player.x, 0xF4FF0F);
	draw_ray(data);
	// mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> mlx.img, 0, 0);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> mlx.img,
							(WIDTH / 2) - ((data -> map.width * BLOC_SIZE) / 2),
							(HEIGHT / 4) - ((data -> map.height *  BLOC_SIZE) / 2));
}

void	draw_gameplay(t_data *data, int add)
{
	if (data -> player.y + add < 0 || data -> player.y + add >= data -> map.height)
		return ;
	data -> player.y += add;
	data -> mlx.img = data -> img_game;
	data -> mlx.addr = data -> game_addr;
	data -> mlx.index = MLX_IMG_GAME;
	for (int y = 0; y < 10 * data -> player.y; y++)
		for (int x = 10; x < GAME_WIDTH - 10; x++)
			mlx_put_pixel(data -> mlx, x, y, 0x000);

	for (int y = GAME_HEIGHT - 10 * data -> player.y; y < GAME_HEIGHT; y++)
		for (int x = 10; x < GAME_WIDTH - 10; x++)
			mlx_put_pixel(data -> mlx, x, y, 0x000);

	for (int y = 10 * data -> player.y; y < GAME_HEIGHT - 10 * data -> player.y; y++)
		for (int x = 10; x < GAME_WIDTH - 10; x++)
			mlx_put_pixel(data -> mlx, x, y, 0x96DED6);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> mlx.img,
							WIDTH - (GAME_WIDTH / 2),
							HEIGHT - (HEIGHT / 2));
}

void	draw_game(t_data *data)
{
	const int	mid = HEIGHT / 2;
	int			*colors;
	int			color;

	colors = (int [2]){set_rgb(data -> map.color_ceil), set_rgb(data -> map.color_floor)};
	data -> mlx.img = data -> img;
	data -> mlx.addr = data -> addr;
	data -> mlx.index = MLX_IMG_MAP;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			mlx_put_pixel(data -> mlx, x, y, colors[y >= mid]);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> mlx.img, 0, 0);
}
