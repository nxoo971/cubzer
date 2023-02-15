/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/15 01:20:15 by jewancti         ###   ########.fr       */
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
			if (add < 0)
				data -> ray.begin_vertical = y - direction - 1;
			else
				data -> ray.end_vertical = abs(y - direction);
			data -> ray.oppose = (data -> ray.end_vertical * BLOC_SIZE) + (data -> ray.begin_vertical * BLOC_SIZE);
			break ;
		}
		i = -1;
		while (++i < BLOC_SIZE)
			mlx_put_pixel(data -> mlx, x * BLOC_SIZE + (BLOC_SIZE / 2), direction * BLOC_SIZE + i, set_rgb((int [3]){250, 183, 29})); // orange
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
			if (direction > 0 && direction < data -> map.width && data -> map.map[y][direction] == WALL)
			{
				// prend la taille du rayon
				if (add < 0)
					data -> ray.begin_horizontal = abs(x - direction) - 1;
				else
					data -> ray.end_horizontal = abs(x - direction);
				data -> ray.adjacent = (data -> ray.end_horizontal * BLOC_SIZE) + (data -> ray.begin_horizontal * BLOC_SIZE);
			}
			break ;
		}
		i = -1;
		while (++i < BLOC_SIZE)
			mlx_put_pixel(data -> mlx, direction * BLOC_SIZE + i, y * BLOC_SIZE + (BLOC_SIZE / 2), set_rgb((int [3]){29, 250, 39})); // green
		direction += add;
	}
}

void	draw_ray(t_data *data)
{
	const int	y = data -> player.y;
	const int	x = data -> player.x;

	// draw_ray_horizontal(data, + 1);
	// draw_ray_horizontal(data, - 1);
	// draw_ray_vertical(data, + 1);
	// draw_ray_vertical(data, - 1);
	// bresenham_line(data -> mlx, (x + .5) * BLOC_SIZE, (y + data -> ray.end_vertical) * BLOC_SIZE, (x + data -> ray.end_horizontal) * BLOC_SIZE, (y + .5) * BLOC_SIZE);
	// bresenham_line(data -> mlx, (x + .5) * BLOC_SIZE, (y + data -> ray.end_vertical) * BLOC_SIZE, (x - data -> ray.begin_horizontal) * BLOC_SIZE, (y + .5) * BLOC_SIZE);
	// bresenham_line(data -> mlx, (x + .5) * BLOC_SIZE, (y - data -> ray.begin_vertical) * BLOC_SIZE, (x - data -> ray.begin_horizontal) * BLOC_SIZE, (y + .5) * BLOC_SIZE);
	// bresenham_line(data -> mlx, (x + .5) * BLOC_SIZE, (y - data -> ray.begin_vertical) * BLOC_SIZE, (x + data -> ray.end_horizontal) * BLOC_SIZE, (y + .5) * BLOC_SIZE);
	bresenham_line(data -> mlx, x * BLOC_SIZE,
								y * BLOC_SIZE,
								(x + cos(data -> player.rotation_angle) * 5) * BLOC_SIZE,
								(y + sin(data -> player.rotation_angle) * 5) * BLOC_SIZE);
	// bresenham_circle(data -> mlx, (x + .5) * BLOC_SIZE, (y + .5) * BLOC_SIZE, 20);
}
