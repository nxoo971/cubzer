/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 04:53:37 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
void draw_ray_vertical(t_mlx mlx, int start, int end, int x, int color)
{
	while (start <= end)
		mlx_put_pixel(mlx, start++, x, color);
}

void draw_buff(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			((int *)data -> addr)[y * WIDTH + x] = data -> buf[y][x];
	}
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> img, 0, 0);
}

static
void calc_step_init_sidedist(t_player player, t_params *params, int map_y, int map_x)
{
	if (params -> ray_x < 0)
	{
		params -> step_x = -1;
		params -> side_x = (player.x - map_x) * params -> delta_x;
	}
	else
	{
		params -> step_x = 1;
		params -> side_x = (map_x + 1.0 - player.x) * params -> delta_x;
	}
	if (params -> ray_y < 0)
	{
		params -> step_y = -1;
		params -> side_y = (player.y - map_y) * params -> delta_y;
	}
	else
	{
		params -> step_y = 1;
		params -> side_y = (map_y + 1.0 - player.y) * params -> delta_y;
	}
}

static
double dda(t_data *data, t_params *params, int *map_y, int *map_x)
{
	params -> delta_y = 1e30;
	params -> delta_x = 1e30;
	if (params -> ray_y != 0)
		params -> delta_y = fabs(1 / params -> ray_y);
	if (params -> ray_x != 0)
		params -> delta_x = fabs(1 / params -> ray_x);
	calc_step_init_sidedist(data -> player, params, *map_y, *map_x);
	while (42)
	{
		if (params -> side_x < params -> side_y)
		{
			params -> side_x += params -> delta_x;
			*map_x += params -> step_x;
			params -> side = 0;
		}
		else
		{
			params -> side_y += params -> delta_y;
			*map_y += params -> step_y;
			params -> side = 1;
		}
		if (data->map.map[*map_y][*map_x] == WALL)
			break;
	}
	if (params -> side == 0)
		return ((*map_x - data->player.x + (1 - params -> step_x) / 2) / params -> ray_x);
	return ((*map_y - data->player.y + (1 - params -> step_y) / 2) / params -> ray_y);
}

void draw_gameplay(t_data *data)
{
	const t_map	map = data->map;
	t_params	*params;
	t_player	*player;
	int			y;
	int			x;

	params = & data -> params;
	player = & data -> player;
	//params -> re_buf = false;//???
	//ft_bzero(data -> buf, HEIGHT * WIDTH);
	y = player->y;
	x = player->x;
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		params -> ray_y = params -> dir_y + params -> plane_y * cameraX;
		params -> ray_x = params -> dir_x + params -> plane_x * cameraX;

		int mapX = (int)player->x;
		int mapY = (int)player->y;
		double perpWallDist = dda(data, params, &mapY, &mapX);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int texNum = 1;

		double wallX;
		if (params -> side == 0)
			wallX = data->player.y + perpWallDist * params -> ray_y;
		else
			wallX = data->player.x + perpWallDist * params -> ray_x;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(TEXTURE_WIDTH));
		if (params -> side == 0 && params -> ray_x > 0)
			texX = TEXTURE_WIDTH - texX - 1;
		if (params -> side == 1 && params -> ray_y < 0)
			texX = TEXTURE_WIDTH - texX - 1;
		double step = 1.0 * TEXTURE_HEIGHT / lineHeight;
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = 0; y < HEIGHT; y++)
		{
			int color;
			if (y < drawStart)
				color = 0xFF0000;
			else if (y > drawEnd)
				color = 0x0000FF;
			else
			{
				int texY = (int)texPos & (TEXTURE_HEIGHT - 1);
				texPos += step;
				if (params -> side == 1)
				{
					if (params -> ray_y > 0)
						color = data->texture[0][TEXTURE_HEIGHT * texY + texX];
					else
						color = data->texture[1][TEXTURE_HEIGHT * texY + texX];
				}
				else
				{
					if (params -> ray_x > 0)
						color = data->texture[3][TEXTURE_HEIGHT * texY + texX];
					else
						color = data->texture[2][TEXTURE_HEIGHT * texY + texX];
				}
			}
			data->buf[y][x] = color;
			params -> re_buf = true;
		}
	}

	draw_buff(data);
}
