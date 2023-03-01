/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:48:11 by rferradi          #+#    #+#             */
/*   Updated: 2023/03/01 03:11:01 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void sort_order(t_pair *orders, int amount)
{
	t_pair tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void sortSprites(int *order, double *dist, int amount)
{
	t_pair *sprites;

	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int count_hamoud(char **map)
{
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'H')
				k++;
	}
	return (k);
}

void parse_sprite(t_data *data, char **map)
{
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'H')
			{
				data->sprite[k].x = j + 0.5;
				data->sprite[k].y = i + 0.5;
				if (j % 2 == 0)
					data->sprite[k++].texture = 8;
				else
					data->sprite[k++].texture = 10;
			}
			j++;
		}
	}
}

int malloc_sprite(t_data *data)
{
	int i;

	data->numhamoud = count_hamoud(data->map.map);
	if (data->numhamoud <= 0)
		return (EXIT_FAILURE);
	ft_printf("numhamoud = %d\n", data->numhamoud);
	data->sprite = (t_sprite *)malloc(sizeof(t_sprite) * (data->numhamoud));
	data->sprite_ord = malloc(sizeof(int) * (data->numhamoud));
	data->sprite_dis = malloc(sizeof(double) * (data->numhamoud));
	if (!data->sprite_ord || !data->sprite_dis || !data->sprite)
		return (EXIT_FAILURE);
	parse_sprite(data, data->map.map);
	return (EXIT_SUCCESS);
}

void sprite_casting(t_data *data, t_player *player, t_params *params)
{
	int i;
	i = -1;
	while (++i < data->numhamoud)
	{
		data->sprite_ord[i] = i;
		data->sprite_dis[i] = ((player->x - data->sprite[i].x) * (player->x - data->sprite[i].x) + (player->y - data->sprite[i].y) * (player->y - data->sprite[i].y)); // sqrt not taken, unneeded
	}
	sortSprites(data->sprite_ord, data->sprite_dis, data->numhamoud - 1);
}

void sprite_cast2(t_data *data, t_player *player, t_params *p, int i)
{
	p->sprite_x = data->sprite[data->sprite_ord[i]].x - player->x;
	p->sprite_y = data->sprite[data->sprite_ord[i]].y - player->y;
	p->invdet = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y); // required for correct matrix multiplication
	p->transform_x = p->invdet * (p->dir_y * p->sprite_x - p->dir_x * p->sprite_y);
	p->transform_y = p->invdet * (-p->plane_y * p->sprite_x + p->plane_x * p->sprite_y); // this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(data->sprite_dis[i])
	p->sprite_screen_x = (int)((WIDTH / 2) * (1 + p->transform_x / p->transform_y));
	p->vmovescreen = (int)(vMove / p->transform_y);
	p->sprite_height = (int)fabs((HEIGHT / p->transform_y) / vDiv); // using "p->transform_y" instead of the real distance prevents fisheye
	p->draw_start_y = -p->sprite_height / 2 + HEIGHT / 2 + p->vmovescreen;
	if (p->draw_start_y < 0)
		p->draw_start_y = 0;
	p->draw_end_y = p->sprite_height / 2 + HEIGHT / 2 + p->vmovescreen;
	if (p->draw_end_y >= HEIGHT)
		p->draw_end_y = HEIGHT - 1;
	p->sprite_width = (int)fabs((HEIGHT / p->transform_y) / uDiv);
	p->draw_start_x = -p->sprite_width / 2 + p->sprite_screen_x;
	if (p->draw_start_x < 0)
		p->draw_start_x = 0;
	p->draw_end_x = p->sprite_width / 2 + p->sprite_screen_x;
	if (p->draw_end_x >= WIDTH)
		p->draw_end_x = WIDTH - 1;
}

void	cast_sprite(t_data *data, t_params *p, int stripe, int i)
{
	int y;
	int d;
	int tex_y;

	y = p->draw_start_y;
	while (y < p->draw_end_y) // for every pixel of the current stripe
	{
		d = (y - p->vmovescreen) * 256 - HEIGHT * 128 + p->sprite_height * 128; // 256 and 128 factors to avoid floats
		p->tex_y = ((d * TEXTURE_HEIGHT) / p->sprite_height) / 256;
		p->color = ((int **)data->texture)[data->sprite[data->sprite_ord[i]].texture][TEXTURE_WIDTH * p->tex_y + p->tex_x]; // get current color from the texture
		if ((p->color & 0x00FFFFFF) != 0)
			data->buf[y][stripe] = p->color; // paint pixel if it isn't black, black is the invisible color
		y++;
	}
}

void begin_sprite(t_data *data, t_player *player, t_params *p)
{
	int i;
	int stripe;
	int y;

	sprite_casting(data, player, p);
	i = -1;
	while (++i < data->numhamoud)
	{
		sprite_cast2(data, player, p, i);
		stripe = p->draw_start_x;
		while (stripe < p->draw_end_x)
		{
			p->tex_x = (int)((256 * (stripe - (-p->sprite_width / 2 + p->sprite_screen_x)) * TEXTURE_WIDTH / p->sprite_width) / 256);
			if (p->transform_y > 0 && stripe > 0 && stripe < WIDTH && p->transform_y < data->zbuffer[stripe])
				cast_sprite(data, p, stripe, i);
			stripe++;
		}
	}
}