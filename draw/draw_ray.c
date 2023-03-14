/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/14 19:12:09 by rferradi         ###   ########.fr       */
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

void	check_door2(t_player *player, t_map *m, t_vect door, int *d)
{
	int	x;
	int	y;

	x = door.x - 2;
	y = door.y - 2;
	while (x <= door.x + 2)
	{
		if ((int)(player->x) == x )
			*d = 1;
		while (y <= door.y + 2)
			y++;
		x++;
	}
	if (*d == 1)
		m->map[door.y][door.x] = '0';
}



void	check_door(t_player *player, t_map *m, t_vect door)
{
	int x;
	int	y;
	int isdoor;

	m->map[door.y][door.x] = 'D';
	x = door.x - 2;
	y = door.y - 2;
	isdoor = 0;
	while (y <= door.y + 2)
	{
		if ((int)(player->x) == x && (int)(player->y) == y)
			isdoor = 1;
		while (x <= door.x + 2)
			x++;
		y++;
	}
	check_door2(player, m, door, &isdoor);
}

void	draw_gameplay(t_data *data)
{
	data->params.test = 0;
	int i = -1;
	while (++i < data->map.nb_door)
		check_door(&data -> player, &data->map, data->map.door[i]);
	loop(data);
	begin_sprite(data, &data->player, &data->params);
	mini_map(data);
	draw_buff(data);
}
