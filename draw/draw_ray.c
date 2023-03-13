/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/13 19:54:24 by rferradi         ###   ########.fr       */
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
		if (data -> map.map[*map_y][*map_x] == 'D')
		{
			// data -> map.map[*map_y][*map_x] = '0';
			params->test = 1;
			break;
		}
			params->test = 0;
		if (data -> map.map[*map_y][*map_x] == WALL)
			break;
	}
	if (params -> side == 0)
		return ((*map_x - data -> player.x + (1 - params -> step_x) / 2) / params -> ray_x);
	return ((*map_y - data -> player.y + (1 - params -> step_y) / 2) / params -> ray_y);
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
		data->zbuffer[x] = perp_wall_dist;
	}
}

void	check_door(char **map, t_player *player, t_map *m)
{
	int i = 0;
	int x, y;
	int door = 0;

	x = m->door.x - 2;
	y = m->door.y - 2;
	map[m->door.y][m->door.x] = 'D';
	printf("DOOR CLOSED\n");
	// printf("door y = %d, door x = %d\n", m->door.y, m->door.x);
	if (y<0)
		y = 0;
	if (x<0)
		x = 0;
	printf("ENTER\n");
	while (y <= m->door.y + 2)
	{
		if ((int)(player->x) == x && (int)(player->y) == y)
			door = 1;
		printf("player y = %d, player x = %d\ny = %d, x = %d\n", (int)(player->y), (int)(player->x), y, x);
		while (x <= m->door.x + 2)
			x++;
		y++;
	}
	x = m->door.x - 2;
	y = m->door.y - 2;
	while (x <= m->door.x + 2)
	{
		if ((int)(player->x) == x )
			door = 1;
		// printf("player y = %d, player x = %d\ny = %d, x = %d\n", (int)(player->y), (int)(player->x), y, x);
		while (y <= m->door.y + 2)
			y++;
		x++;
	}
	if (door == 1)
		map[m->door.y][m->door.x] = '0';
}

void	draw_gameplay(t_data *data)
{
	data->params.test = 0;
	int i = 0;
	check_door(data->map.map, &data -> player, &data->map);
	loop(data);
	check_door(data->map.map, &data -> player, &data->map);
	begin_sprite(data, &data->player, &data->params);
	mini_map(data);
	draw_buff(data);
}
