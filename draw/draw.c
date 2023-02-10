/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:28:27 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/10 02:41:09 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
void	draw_ray_vertical(t_data *data, int add)
{
	const int	y = data -> player.y;
	const int	x = data -> player.x;
	int			direction;
	int			i;

	direction = y + add;
	while (1)
	{
		if (direction < 0 || direction >= data -> map.height || data -> map.map[direction][x] == WALL)
		{
			if (data -> map.map[direction][x] == WALL)
			{
				if (add < 0)
					data -> ray.begin_vertical = y - direction;
				else
					data -> ray.end_vertical = abs(y - direction);
				data -> ray.oppose = (data -> ray.end_vertical * SIZE_BLOC) + (data -> ray.begin_vertical * SIZE_BLOC);
			}
			break ;
		}
		i = -1;
		while (++i < SIZE_BLOC)
			mlx_put_pixel(data -> mlx, x * SIZE_BLOC + (SIZE_BLOC / 2), direction * SIZE_BLOC + i, set_rgb((int [3]){250, 183, 29})); // orange
		direction += add;
	}
}

static
void	draw_ray_horizontal(t_data *data, int add)
{
	const int	y = data -> player.y;
	const int	x = data -> player.x;
	int			direction;
	int			i;

	direction = x + add;
	while (1)
	{
		if (direction < 0 || direction >= data -> map.width || data -> map.map[y][direction] == WALL)
		{
			if (data -> map.map[y][direction] == WALL)
			{
				if (add < 0)
					data -> ray.begin_horizontal = abs(x - direction);
				else
					data -> ray.end_horizontal = abs(x - direction);
				data -> ray.adjacent = (data -> ray.end_horizontal * SIZE_BLOC) + (data -> ray.begin_horizontal * SIZE_BLOC);
			}
			break ;
		}
		i = -1;
		while (++i < SIZE_BLOC)
			mlx_put_pixel(data -> mlx, direction * SIZE_BLOC + i, y * SIZE_BLOC + (SIZE_BLOC / 2), set_rgb((int [3]){29, 250, 39})); // green
		direction += add;
	}
	//data -> ray.horizontal_x = 
}

static
void	draw_ray(t_data *data)
{
	draw_ray_horizontal(data, + 1);
	draw_ray_horizontal(data, - 1);
	draw_ray_vertical(data, + 1);
	draw_ray_vertical(data, - 1);
	//for (int i = 0; i < 20; i++)	
		//BresenhamLine(data -> mlx, data -> player.x * SIZE_BLOC - i, data -> player.y * SIZE_BLOC + i, data -> player.x * SIZE_BLOC, data -> player.y * SIZE_BLOC);
	//printf("Player x: %d | Player y: %d\n", data -> player.x, data -> player.y);
	//printf("END VERTICAL x: %d | END HORIZONRTAL y: %d\n", data -> ray.end_vertical, data -> ray.end_horizontal);
	//BresenhamLine(data -> mlx, 0, 12 * SIZE_BLOC,
	//				19 * SIZE_BLOC, 11 * SIZE_BLOC);
	//BresenhamLine(data -> mlx, data -> ray.end_horizontal * SIZE_BLOC, data -> player.y * SIZE_BLOC,
	//				data -> player.x * SIZE_BLOC, data -> ray.end_vertical * SIZE_BLOC);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> mlx.img,
								(WIDTH / 2) - ((data -> map.width * SIZE_BLOC) / 2),
								(HEIGHT / 4) - ((data -> map.height *  SIZE_BLOC) / 2));
}

void	draw_map(t_data *data)
{
	const int	height = data -> map.height;
	const int	width = data -> map.width;
	int			color;
	char		**map;
	int			minimap_height, minimap_width;

	map = data -> map.map;
	int size = SIZE_BLOC;
	minimap_height = height * size;
	minimap_width = width * size;
	if (data -> img_map)
		mlx_destroy_image(data -> mlx_ptr, data -> img_map);
	data -> img_map = mlx_new_image(data -> mlx_ptr, minimap_width, minimap_height);
	data -> img_addr = mlx_get_data_addr(data -> img_map, & data -> mlx.bits_per_pixel, & data -> mlx.line_length, & data -> mlx.endian);
	data -> mlx.img = data -> img_map;
	data -> mlx.addr = data -> img_addr;
	for (size_t y = 0; y < height; y++)
		for (size_t x = 0; x < map[y][x]; x++)
			for (size_t t = 0; t < size; t++)
				for (size_t r = 0; r < size; r++)
				{
					if (map[y][x] == WALL)
						color = set_rgb((int [3]){205, 53, 45});
					if (map[y][x] == BLANK)
						color = set_rgb((int [3]){25, 79, 126});
					if (map[y][x] == 'N')
						color = set_rgb((int [3]){55, 12, 53});
					mlx_put_pixel(data -> mlx, r + (x * size), t + (y * size), color);
				}
	draw_ray(data);
	//ft_printf("Premier rayon touchant un mur: \n");
	//ft_printf("\tbegin_vertical: %d | end_vertical: %d\n", data->ray.begin_vertical, data->ray.end_vertical);
	//ft_printf("\tbegin_horizontal: %d | end_horizontal: %d\n", data->ray.begin_horizontal, data->ray.end_horizontal);
	//ft_printf("\tOppose: %d | Adjacent: %d\n", data->ray.oppose, data->ray.adjacent);
	//ft_printf("\t\tIntersection au player\n"); // a finir intersection
	//ft_printf("\t\t\tOppose: %d | Adjacent: %d\n", abs((data->player.x * SIZE_BLOC) - data->ray.oppose), abs((data->player.x * SIZE_BLOC) - data->ray.adjacent));
	//ft_printf("end x %d | end y %d\n", data->ray.end_horizontal, data->ray.end_vertical);
	//ft_printf("start x %d\n", data->ray.begin_horizontal);
	//ft_printf("data->player.x %d\n", data->player.x);
	//printf("\t\t\thypo: %f\n", sqrt(pow(data->ray.end_horizontal * SIZE_BLOC, 2) + pow(data->ray.end_vertical * SIZE_BLOC, 2)));
	//printf("\t\t\thypo pas bloc: %f\n", sqrt(pow(data->ray.end_horizontal, 2) + pow(data->ray.end_vertical, 2)));
	//printf("\t\t\tverif: %f\n", sqrt((pow(data->ray.end_horizontal, 2) + pow(data->ray.end_vertical, 2)) - pow(data->ray.end_horizontal, 2)));
	////printf("\tHypothenuse: %d \n", (int)pow(11, 2));// + pow(data->ray.adjacent, 2)));
	//ft_printf("Position du player:\n");
	//ft_printf("\ty: %d | x: %d\n", data -> player.y, data -> player.x);
	//ft_printf("\t---> y: %d | x: %d\n\n\n", data -> player.y, data -> player.x - data->ray.begin_horizontal);
	//ft_printf("\tTaille de la map\n");
	//ft_printf("\tHeight: %d | Width: %d\n", data -> map.height, data -> map.width);
}

void        BresenhamLine(t_mlx mlx, int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    mlx_put_pixel(mlx, x0, y0, 0xF14457);    
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void	draw(t_data *data)
{
	int		floor;
	int		ceil;

	ceil = set_rgb(data -> map.color_ceil);
	floor = set_rgb(data -> map.color_floor);
	data -> img = mlx_new_image(data -> mlx_ptr, WIDTH, HEIGHT);
	data -> addr = mlx_get_data_addr(data -> img, & data -> mlx.bits_per_pixel, & data -> mlx.line_length, & data -> mlx.endian);
	data -> mlx.img = data -> img;
	data -> mlx.addr = data -> addr;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (j > HEIGHT / 2)
				mlx_put_pixel(data -> mlx, i, j, ceil);
			else
				mlx_put_pixel(data -> mlx, i, j, floor);
		}
	}
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> mlx.img, 0, 0);
	draw_map(data);
}
