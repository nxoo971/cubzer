/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:39:55 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/26 22:02:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
int	get_color_from_texture(t_data *data, double *texture_pos,
							int texture_y, int texture_x)
{
	int	color;

	color = 0x0;
	texture_y = (int)*texture_pos & (TEXTURE_HEIGHT - 1);
	*texture_pos += data -> params.step;
	if (data -> params.side == 1)
	{
		if (data -> params.ray_y > 0)
			color = data -> texture[0][TEXTURE_HEIGHT * texture_y + texture_x];
		else
			color = data -> texture[1][TEXTURE_HEIGHT * texture_y + texture_x];
	}
	else
	{
		if (data -> params.ray_x > 0)
			color = data -> texture[3][TEXTURE_HEIGHT * texture_y + texture_x];
		else
			color = data -> texture[2][TEXTURE_HEIGHT * texture_y + texture_x];
	}
	return (color);
}

static
void	end_textures(t_data *data, int x, double text_pos, const int colors[3])
{
	int	y;
	int	color;
	int	texture_y;
	int	texture_x;

	texture_x = colors[0];
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < data -> params.draw_start)
			color = colors[1];
		else if (y > data -> params.draw_end)
			color = colors[2];
		else
			color = get_color_from_texture(data, & text_pos,
					texture_y, texture_x);
		data -> buf[y][x] = color;
		data -> params.re_buf = true;
	}
}

void	begin_textures(t_data *data, int x,
						double perp_wall_dist, int line_height)
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
	texture_pos = (data -> params.draw_start
			- HEIGHT / 2 + line_height / 2) * data -> params.step;
	end_textures(data, x, texture_pos,
		(int [3]){texture_x,
		set_rgb(data -> map.color_ceil), set_rgb(data -> map.color_floor)});
}
