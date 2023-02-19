/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/18 22:38:44 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
void	draw_ray_vertical(t_mlx mlx, int start, int end, int x, int color)
{
	while (start <= end)
		mlx_put_pixel(mlx, start++, x, color);
}

void	draw_gameplay(t_data *data)
{
	t_player	player;

	player = data -> player;
	data -> mlx.addr = data -> addr;
	data -> mlx.img = data -> img;
	for(int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		double rayDirX = player.dir_x + player.plane_x * cameraX;
		double rayDirY = player.dir_y + player.plane_y * cameraX;
		
		int mapX = (int)player.x;
		int mapY = (int)player.y;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

       //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
	 	int stepX;
	  	int stepY;

		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
		}
		//perform DDA
		while (42)
		{
        //jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
        	//Check if ray has hit a wall
			if (data -> map.map[mapY][mapX] == WALL)
				break ;
     	} 
		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;
		      //Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

		int tmpColor;
		if (data -> map.map[mapY][mapX] == WALL)
			tmpColor = 0xF3FF00;
		else
		{
			ft_printf("test\n");
			tmpColor = 0x000000;
		}
		draw_ray_vertical(data -> mlx, drawStart, drawEnd, x, 0xFF0000);
		draw_ray_vertical(data -> mlx, 0, drawStart, x, BLUE);
		draw_ray_vertical(data -> mlx, drawEnd, HEIGHT, x, WHITE);
		x++;
	}
}
