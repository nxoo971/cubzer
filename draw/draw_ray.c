/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/23 22:36:48 by rferradi         ###   ########.fr       */
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

void load_image(t_data *data, int *texture, char *path, t_mlx *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img->img_width, &img->img_height);
	printf("img = %p  | path = %s  \n", img->img, path);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(data->mlx_ptr, img->img);
}

void load_texture(t_data *data)
{
	t_mlx img;

	load_image(data, data->texture[0], "texture/eagle.xpm", &img);
	load_image(data, data->texture[1], "texture/redbrick.xpm", &img);
	load_image(data, data->texture[2], "texture/purplestone.xpm", &img);
	load_image(data, data->texture[3], "texture/greystone.xpm", &img);
	// load_image(data, data->texture[4], "texture/bluestone.xpm", &img);
	// load_image(data, data->texture[5], "texture/mossy.xpm", &img);
	// load_image(data, data->texture[6], "texture/wood.xpm", &img);
	// load_image(data, data->texture[7], "texture/colorstone.xpm", &img);
}

void draw_gameplay(t_data *data)
{
	t_player *player = &data->player;
	t_map map = data->map;
	const int y = player->y;
	const int x = player->x;
	player->re_buf = 0;

	// 	data -> mlx.addr = data -> addr;
	// 	data -> mlx.img = data -> img;

	// 		for (int i = 0; i < HEIGHT; i++)
	// 		{
	// 			//data -> buf[i] = malloc(sizeof(int) * WIDTH);
	// 			for (int j = 0; j < WIDTH; j++)
	// 			{
	// 				data -> buf[i][j] = 0;
	// 			}
	// 		}
	// 		// for (int i = 0; i < HEIGHT; i++)
	// 		// {
	// 		// 	for (int j = 0; j < WIDTH; j++)
	// 		// 	{
	// 		// 		data->buf[i][j] = 0;
	// 		// 	}
	// 		// }

	// 		if (!(data -> texture = (int **)malloc(sizeof(int *) * 8)))
	// 			return ;
	// 		for (int i = 0; i < 8; i++)
	// 		{
	// 			if (!(data -> texture[i] = (int *)malloc(sizeof(int) * (textheight * textwidth))))
	// 				return ;
	// 		}
	// 		for (int i = 0; i < 8; i++)
	// 		{
	// 			for (int j = 0; j < textheight * textwidth; j++)
	// 			{
	// 				data -> texture[i][j] = 0;
	// 			}
	// 		}
	// load_texture(data);
	// if (player->re_buf == 1)
	// {
	// 	for (int i = 0; i < HEIGHT; i++)
	// 	{
	// 		for (int j = 0; j < WIDTH; j++)
	// 		{
	// 			data->buf[i][j] = 0;
	// 		}
	// 	}
	// }
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
			wallX = data->player.y + perpWallDist * data->player.dir_y;
		else
			wallX = data->player.x + perpWallDist * data->player.dir_x;
		wallX -= floor((wallX));

		// x coordinate on the texture
		int texX = (int)(wallX * (double)(textwidth));
		if (side == 0 && rayDirX > 0)
			texX = textwidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = textwidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * textheight / lineHeight;
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
				int texY = (int)texPos & (textheight - 1);
				texPos += step;
				if (side == 1)
				{
					if (rayDirY > 0)
						color = data->texture[0][textheight * texY + texX];
					else
						color = data->texture[1][textheight * texY + texX];
				}
				else
				{
					if (rayDirX > 0)
						color = data->texture[3][textheight * texY + texX];
					else
						color = data->texture[2][textheight * texY + texX];
				}
			}
			data->buf[y][x] = color;
			player->re_buf = 1;
		}
		//  draw_ray_vertical(data -> mlx, drawStart, drawEnd, x, tmpColor);
		// draw_ray_vertical(data -> mlx, 0, drawStart, x, BLUE);
		// draw_ray_vertical(data -> mlx, drawEnd, HEIGHT, x, WHITE);
	}

	draw_buff(data);
}
