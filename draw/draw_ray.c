/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/20 18:03:19 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
void	draw_ray_vertical(t_mlx mlx, int start, int end, int x, int color)
{
	while (start <= end)
		mlx_put_pixel(mlx, start++, x, color);
}

static
void	calc_step_init_sidedist(t_player player,
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

static
double	dda(t_data *data,
			int *map_y, int *map_x,
			double ray_y, double ray_x)
{
	double	perpWallDist;
	double	delta_y;
	double	delta_x;
	double	side_y;
	double	side_x;
	int		step_y;
	int		step_x;
	int		side;

	delta_y = 1e30;
	delta_x = 1e30;
	if (ray_y != 0)
		delta_y = fabs(1 / ray_y);
	if (ray_x != 0)
		delta_x = fabs(1 / ray_x);
	calc_step_init_sidedist(data -> player, & step_y, & step_x,
								*map_y, *map_x, ray_y, ray_x, delta_y, delta_x, & side_y, & side_x);
	while (42)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			*map_x += step_x;
			side = 0;
		}
		else
		{
			side_y += delta_y;
			*map_y += step_y;
			side = 1;
		}
		if (data -> map.map[*map_y][*map_x] == WALL)
			break ;
	}
	if (side == 0)
		return (side_x - delta_x);
	return (side_y - delta_y);
}

void	draw_gameplay(t_data *data)
{
	t_player	player;

	player = data -> player;
	data -> mlx.addr = data -> addr;
	data -> mlx.img = data -> img;
	for(int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = player.dir_x + player.plane_x * cameraX;
		double rayDirY = player.dir_y + player.plane_y * cameraX;
		
		int mapX = (int)player.x;
		int mapY = (int)player.y;
		double perpWallDist = dda(data, & mapY, & mapX, rayDirY, rayDirX);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		if (lineHeight <= 0)
			lineHeight = 100000;
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int tmpColor;
		if (data -> map.map[mapY][mapX] == WALL)
			tmpColor = 0xF3FF00;
		else
		{
			ft_printf("test\n");
			tmpColor = 0x000000;
		}
		draw_ray_vertical(data -> mlx, drawStart, drawEnd, x, tmpColor);
		draw_ray_vertical(data -> mlx, 0, drawStart, x, BLUE);
		draw_ray_vertical(data -> mlx, drawEnd, HEIGHT, x, WHITE);
		x++;
	}
}