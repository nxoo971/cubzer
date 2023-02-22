/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/21 22:26:45 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int tmpcol = 0;

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
			double *ray_y, double *ray_x, int *side)
{
	double	perpWallDist;
	double	delta_y;
	double	delta_x;
	double	side_y;
	double	side_x;
	int		step_y;
	int		step_x;

	delta_y = 1e30;
	delta_x = 1e30;
	if (*ray_y != 0)
		delta_y = fabs(1 / *ray_y);
	if (*ray_x != 0)
		delta_x = fabs(1 / *ray_x);
	calc_step_init_sidedist(data -> player, & step_y, & step_x,
								*map_y, *map_x, *ray_y, *ray_x, delta_y, delta_x, & side_y, & side_x);
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
		if (data -> map.map[*map_y][*map_x] == WALL)
			break ;
	}
	if (*side == 0)
		return (side_x - delta_x);
	return (side_y - delta_y);
}

void	draw_gameplay(t_data *data)
{
	t_player	player;
	t_map		map;
	const int	y = player.y;
	const int	x = player.x;

	player = data -> player;
	data -> mlx.addr = data -> addr;
	data -> mlx.img = data -> img;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < textheight * textwidth; j++)
		{
			data->texture[i][j] = 0;
		}
	}

	for (int x = 0; x < textwidth; x++)
	{
		for (int y = 0; y < textheight; y++)
		{
			int xorcolor = (x * 256 / textwidth) ^ (y * 256 / textheight);
			int ycolor = y * 256 / textheight;
			int xycolor = y * 128 / textheight + x * 128 / textwidth;
			data->texture[0][textwidth * y + x] = 65536 * 254 * (x != y && x != textwidth - y); //flat red texture with black cross
			data->texture[1][textwidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			data->texture[2][textwidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			data->texture[3][textwidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			data->texture[4][textwidth * y + x] = 256 * xorcolor; //xor green
			data->texture[5][textwidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			data->texture[6][textwidth * y + x] = 65536 * ycolor; //red gradient
			data->texture[7][textwidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

	for(int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = player.dir_x + player.plane_x * cameraX;
		double rayDirY = player.dir_y + player.plane_y * cameraX;
		
		int mapX = (int)player.x;
		int mapY = (int)player.y;
		int side;
		double perpWallDist = dda(data, & mapY, & mapX, & rayDirY, & rayDirX, & side);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		if (lineHeight <= 0)
			lineHeight = 100000;
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int tmpColor = tmpcol;

		// if (data -> map.map[mapY][mapX] == WALL)
			// tmpColor = 0xabcdef;

      //texturing calculations
      int texNum = map.map[y][x]; // -1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = data->player.y + perpWallDist * data->player.dir_y;
      else           wallX = data->player.x + perpWallDist * data->player.dir_x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (textwidth));
      if(side == 0 && rayDirX > 0) texX = textwidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = textwidth - texX - 1;

		draw_ray_vertical(data -> mlx, drawStart, drawEnd, x, tmpColor);
		draw_ray_vertical(data -> mlx, 0, drawStart, x, BLUE);
		draw_ray_vertical(data -> mlx, drawEnd, HEIGHT, x, WHITE);
		x++;
	}
}