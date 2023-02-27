/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/27 02:51:27 by jewancti         ###   ########.fr       */
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
void	calc_step_and_side_dist(t_player player, t_params *params,
								int map_y, int map_x)
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
double	get_perp_wall_dist(t_data *data, int map_y, int map_x)
{
	if (data -> params.side == 0)
		return ((map_x - data -> player.x
				+ (1 - data -> params.step_x) / 2) / data -> params.ray_x);
	return ((map_y - data -> player.y
			+ (1 - data -> params.step_y) / 2) / data -> params.ray_y);
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
			break ;
	}
	return (get_perp_wall_dist(data, *map_y, *map_x));
}

void	draw_gameplay(t_data *data)
{
	double	perp_wall_dist;
	double	ca_x;
	int		line_height;
	int		p_yx[2];
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		ca_x = 2 * x / (double)WIDTH - 1;
		data->params.ray_y = data->params.dir_y + data->params.plane_y * ca_x;
		data->params.ray_x = data->params.dir_x + data->params.plane_x * ca_x;
		p_yx[0] = (int)data -> player.y;
		p_yx[1] = (int)data -> player.x;
		perp_wall_dist = dda(data, & data -> params, & p_yx[0], & p_yx[1]);
		line_height = (int)(HEIGHT / perp_wall_dist);
		data -> params.draw_start = -line_height / 2 + HEIGHT / 2;
		if (data -> params.draw_start < 0)
			data -> params.draw_start = 0;
		data -> params.draw_end = line_height / 2 + HEIGHT / 2;
		if (data -> params.draw_end >= HEIGHT)
			data -> params.draw_end = HEIGHT - 1;
		begin_textures(data, x, perp_wall_dist, line_height);
	}
	draw_buff(data);
}
