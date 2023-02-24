/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 21:31:07 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	draw_buff(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			((int *)data->addr)[y * WIDTH + x] = data->buf[y][x];
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

static
void	calc_step_and_side_dist(t_player player, t_params *params, int map_y, int map_x)
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
double	dda(t_data *data, t_params *params, int *map_y, int *map_x)
{
	params -> delta_y = 1e30;
	params -> delta_x = 1e30;
	if (params -> ray_y != 0)
		params -> delta_y = fabs(1 / params -> ray_y);
	if (params -> ray_x != 0)
		params -> delta_x = fabs(1 / params -> ray_x);
	calc_step_and_side_dist(data -> player, params, *map_y, *map_x);
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
		if (data -> map.map[*map_y][*map_x] == WALL)
			break;
	}
	if (params -> side == 0)
		return ((*map_x - data -> player.x + (1 - params -> step_x) / 2) / params -> ray_x);
	return ((*map_y - data -> player.y + (1 - params -> step_y) / 2) / params -> ray_y);
}


static
void	end_textures(t_data *data, int x, int texture_pos, const int texture_x, const int colors[2])
{
	int	y;
	int	texture_y;
	int	color;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < data -> params.draw_start)
			color = colors[0];
		else if (y > data -> params.draw_end)
			color = colors[1];
		else
		{
			texture_y = (int)texture_pos & (TEXTURE_HEIGHT - 1);
			texture_pos += data -> params.step;
			if (data -> params.side == 1)
			{
				if (data -> params.ray_y > 0)
					color = data->texture[0][TEXTURE_HEIGHT * texture_y + texture_x];
				else
					color = data->texture[1][TEXTURE_HEIGHT * texture_y + texture_x];
			}
			else
			{
				if (data -> params.ray_x > 0)
					color = data->texture[3][TEXTURE_HEIGHT * texture_y + texture_x];
				else
					color = data->texture[2][TEXTURE_HEIGHT * texture_y + texture_x];
			}
		}
		data->buf[y][x] = color;
		data -> params.re_buf = true;
	}
}

static
void	begin_textures(t_data *data, int x, double perp_wall_dist, int line_height)
{
	double	wall_x;
	double	texture_pos;
	int		texture_x;

	if (data -> params.side == 0)
		wall_x = data -> player.y + perp_wall_dist * data -> params.ray_y;
	else
		wall_x = data -> player.x + perp_wall_dist * data -> params.ray_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)(TEXTURE_WIDTH));
	if (data -> params.side == 0 && data -> params.ray_x > 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	if (data -> params.side == 1 && data -> params.ray_y < 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	data -> params.step = 1.0 * TEXTURE_HEIGHT / line_height;
	texture_pos = (data -> params.draw_start - HEIGHT / 2 + line_height / 2) * data -> params.step;
	end_textures(data, x, texture_pos, texture_x,
					(int [2]){set_rgb(data -> map.color_ceil), set_rgb(data -> map.color_floor)});
	for (int y = 0; y < HEIGHT; y++)
	{
		int color;
		if (y < data -> params.draw_start)
			color = set_rgb(data -> map.color_ceil);
		else if (y > data -> params.draw_end)
			color = set_rgb(data -> map.color_floor);
		else
		{
			int texY = (int)texture_pos & (TEXTURE_HEIGHT - 1);
			texture_pos += data -> params.step;
			if (data -> params.side == 1)
			{
				if (data -> params.ray_y > 0)
					color = data->texture[0][TEXTURE_HEIGHT * texY + texture_x];
				else
					color = data->texture[1][TEXTURE_HEIGHT * texY + texture_x];
			}
			else
			{
				if (data -> params.ray_x > 0)
					color = data->texture[3][TEXTURE_HEIGHT * texY + texture_x];
				else
					color = data->texture[2][TEXTURE_HEIGHT * texY + texture_x];
			}
		}
		data->buf[y][x] = color;
		data -> params.re_buf = true;
	}
}

static
void	loop(t_data *data)
{
	double	perp_wall_dist;
	double	camera_x;
	int		line_height;
	int		p_x;
	int		p_y;

	for (int x = 0; x < WIDTH; x++)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		data -> params.ray_y = data -> params.dir_y + data -> params.plane_y * camera_x;
		data -> params.ray_x = data -> params.dir_x + data -> params.plane_x * camera_x;
		p_x = (int)data -> player.x;
		p_y = (int)data -> player.y;
		perp_wall_dist = dda(data, & data -> params, & p_y, & p_x);
		line_height = (int)(HEIGHT / perp_wall_dist);
		data -> params.draw_start = -line_height / 2 + HEIGHT / 2;
		if (data -> params.draw_start < 0)
			data -> params.draw_start = 0;
		data -> params.draw_end = line_height / 2 + HEIGHT / 2;
		if (data -> params.draw_end >= HEIGHT)
			data -> params.draw_end = HEIGHT - 1;
		begin_textures(data, x, perp_wall_dist, line_height);
	}
}


void	draw_gameplay(t_data *data)
{
	loop(data);
	//const t_map	map = data->map;
	//t_params	*params;
	//t_player	*player;
	//int			y;
	//int			x;

	//params = & data -> params;
	//player = & data -> player;
	////params -> re_buf = false;//???
	//y = player->y;
	//x = player->x;
	//for (int x = 0; x < WIDTH; x++)
	//{
	//	double cameraX = 2 * x / (double)WIDTH - 1;
	//	params -> ray_y = params -> dir_y + params -> plane_y * cameraX;
	//	params -> ray_x = params -> dir_x + params -> plane_x * cameraX;

	//	int mapX = (int)player->x;
	//	int mapY = (int)player->y;
	//	double perpWallDist = dda(data, params, &mapY, &mapX);

	//	int lineHeight = (int)(HEIGHT / perpWallDist);
	//	int drawStart = -lineHeight / 2 + HEIGHT / 2;
	//	if (drawStart < 0)
	//		drawStart = 0;
	//	int drawEnd = lineHeight / 2 + HEIGHT / 2;
	//	if (drawEnd >= HEIGHT)
	//		drawEnd = HEIGHT - 1;

	//double wallX;
	//	if (data -> params.side == 0)
	//		wallX = data->player.y + perp_wall_dist * data -> params.ray_y;
	//	else
	//		wallX = data->player.x + perp_wall_dist * data -> params.ray_x;
	//	wallX -= floor((wallX));
	//	int texX = (int)(wallX * (double)(TEXTURE_WIDTH));
	//	if (data -> params.side == 0 && data -> params.ray_x > 0)
	//		texX = TEXTURE_WIDTH - texX - 1;
	//	if (data -> params.side == 1 && data -> params.ray_y < 0)
	//		texX = TEXTURE_WIDTH - texX - 1;
	//	double step = 1.0 * TEXTURE_HEIGHT / line_height;
	//	double texPos = (data -> params.draw_start - HEIGHT / 2 + line_height / 2) * step;
	//	for (int y = 0; y < HEIGHT; y++)
	//	{
	//		int color;
	//		if (y < data -> params.draw_start)
	//			color = set_rgb(data -> map.color_ceil);
	//		else if (y > data -> params.draw_end)
	//			color = set_rgb(data -> map.color_floor);
	//		else
	//		{
	//			int texY = (int)texPos & (TEXTURE_HEIGHT - 1);
	//			texPos += step;
	//			if (data -> params.side == 1)
	//			{
	//				if (data -> params.ray_y > 0)
	//					color = data->texture[0][TEXTURE_HEIGHT * texY + texX];
	//				else
	//					color = data->texture[1][TEXTURE_HEIGHT * texY + texX];
	//			}
	//			else
	//			{
	//				if (data -> params.ray_x > 0)
	//					color = data->texture[3][TEXTURE_HEIGHT * texY + texX];
	//				else
	//					color = data->texture[2][TEXTURE_HEIGHT * texY + texX];
	//			}
	//		}
	//		data->buf[y][x] = color;
	//		data -> params.re_buf = true;
	//	}

	draw_buff(data);
}
