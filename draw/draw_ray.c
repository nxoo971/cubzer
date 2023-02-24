/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 02:36:05 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int tmpcol = 0;

static void draw_ray_vertical(t_mlx mlx, int start, int end, int x, int color)
{
	while (start <= end)
		mlx_put_pixel(mlx, start++, x, color);
}

void draw_buff(t_data *data)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			data->addr[y * WIDTH + x] = data->buf[y][x];
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

static void calc_step_init_sidedist(t_player player,
									int *step_y, int *step_x,
									int map_y, int map_x,
									double ray_y, double ray_x,
									double delta_y, double delta_x,
									double *side_y, double *side_x)
{
	if (ray_x < 0)
	{
		*step_x = -1;
		*side_x = (player.x - map_x) * delta_x;
	}
	else
	{
		*step_x = 1;
		*side_x = (map_x + 1.0 - player.x) * delta_x;
	}
	if (ray_y < 0)
	{
		*step_y = -1;
		*side_y = (player.y - map_y) * delta_y;
	}
	else
	{
		*step_y = 1;
		*side_y = (map_y + 1.0 - player.y) * delta_y;
	}
}

static double dda(t_data *data,
				  int *map_y, int *map_x,
				  double *ray_y, double *ray_x, int *side)
{
	double delta_y;
	double delta_x;
	double side_y;
	double side_x;
	int step_y;
	int step_x;

	delta_y = 1e30;
	delta_x = 1e30;
	if (*ray_y != 0)
		delta_y = fabs(1 / *ray_y);
	if (*ray_x != 0)
		delta_x = fabs(1 / *ray_x);
	calc_step_init_sidedist(data->player, &step_y, &step_x,
							*map_y, *map_x, *ray_y, *ray_x, delta_y, delta_x, &side_y, &side_x);
	while (42)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			*map_x += step_x;
			*side = 0;
			tmpcol = 0xe4d0aF;
		}
		else
		{
			side_y += delta_y;
			*map_y += step_y;
			*side = 1;
			tmpcol = 0x123456;
		}
		if (data->map.map[*map_y][*map_x] == WALL)
			break;
	}
	if (*side == 0)
		return ((*map_x - data->player.x + (1 - step_x ) / 2) / *ray_x);
	return ((*map_y - data->player.y + (1 - step_y ) / 2) / *ray_y);
}

void draw_gameplay(t_data *data)
{
	t_player *player = &data->player;
	t_map map = data->map;
	const int y = player->y;
	const int x = player->x;
	player->re_buf = 0;
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = player->dir_x + player->plane_x * cameraX;
		double rayDirY = player->dir_y + player->plane_y * cameraX;

		int mapX = (int)player->x;
		int mapY = (int)player->y;
		int side;
		double perpWallDist = dda(data, &mapY, &mapX, &rayDirY, &rayDirX, &side);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		// if (lineHeight <= 0)
		// 	lineHeight = 100000;
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int tmpColor = tmpcol;

		int texNum = 1; // -1; //1 subtracted from it so that texture 0 can be used!

		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = data->player.y + perpWallDist * rayDirY;
		else
			wallX = data->player.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		// x coordinate on the texture
		int texX = (int)(wallX * (double)(TEXTURE_WIDTH));
		if (side == 0 && rayDirX > 0)
			texX = TEXTURE_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEXTURE_WIDTH - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * TEXTURE_HEIGHT / lineHeight;
		// Starting texture coordinate
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
				if (side == 1)
				{
					if (rayDirY > 0)
						color = data->texture[0][TEXTURE_HEIGHT * texY + texX];
					else
						color = data->texture[1][TEXTURE_HEIGHT * texY + texX];
				}
				else
				{
					if (rayDirX > 0)
						color = data->texture[3][TEXTURE_HEIGHT * texY + texX];
					else
						color = data->texture[2][TEXTURE_HEIGHT * texY + texX];
				}
			}
			data->buf[y][x] = color; // c'est ici que ca segfault
			player->re_buf = 1;
		}
		// draw_ray_vertical(data -> mlx, drawStart, drawEnd, x, tmpColor);
		// draw_ray_vertical(data -> mlx, 0, drawStart, x, BLUE);
		// draw_ray_vertical(data -> mlx, drawEnd, HEIGHT, x, WHITE);
	}

	draw_buff(data);
}
