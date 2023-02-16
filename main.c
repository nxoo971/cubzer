/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/16 19:46:18 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./includes/cub3d.h"

void	mlx_put_pixel(t_mlx mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx.addr + (y * mlx.line_length[mlx.index] + x * (mlx.bits_per_pixel[mlx.index] / 8));
	*(unsigned int *)dst = color;
}

static
void	get_playerpos(t_data *data)
{
	data -> player.delta_y = sin(data -> player.rotation_angle * M_PI / 180.);
	data -> player.delta_x = cos(data -> player.rotation_angle * M_PI / 180.);
	for (int i = 0; i < data -> map.height; i++)
	{
		for (int j = 0; data -> map.map[i][j]; j++)
		{
			if (data -> map.map[i][j] == 'N')
			{
				data -> player.y = i;
				data -> player.x = j;
				return ;
			}
		}
	}
}

static
int	quit(t_data *data)
{
	mlx_loop_end(data -> mlx_ptr);
	return (EXIT_SUCCESS);
}

static
int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		mlx_loop_end(data -> mlx_ptr);
	if (keycode == TOP || keycode == W)
	{
		data -> player.y += data -> player.delta_y * 5;
		data -> player.x += data -> player.delta_x * 5;
		// data -> player.walk_direction = + 1;
	}
	if (keycode == DOWN || keycode == S)
	{
		data -> player.y -= data -> player.delta_y * 5;
		data -> player.x -= data -> player.delta_x * 5;
		// data -> player.walk_direction = - 1;
	}
	if (keycode == LEFT || keycode == A)
	{
		data -> player.rotation_angle += 5;
		data -> player.delta_y = -sin(data -> player.rotation_angle * M_PI / 180.);
		data -> player.delta_x = cos(data -> player.rotation_angle * M_PI / 180.);
		// data -> player.view_direction = - 1;
	}
	if (keycode == RIGHT || keycode == D)
	{
		data -> player.rotation_angle -= 5;
		data -> player.delta_y = -sin(data -> player.rotation_angle * M_PI / 180.);
		data -> player.delta_x = cos(data -> player.rotation_angle * M_PI / 180.);
		// data -> player.view_direction = + 1;
	}
	draw_minimap(data);
	if (keycode == TOP || keycode == W)
		data -> player.walk_direction = 0;
	if (keycode == DOWN || keycode == S)
		data -> player.walk_direction = 0;
	if (keycode == LEFT || keycode == A)
		data -> player.view_direction = 0;
	if (keycode == RIGHT || keycode == D)
		data -> player.view_direction = 0;
	print_map(*data);
	return (0);
}

static
int	lunch_game(t_data *data)
{
	if (init_mlx(data))
		return (EXIT_FAILURE);
	if (init_map(data))
		return (EXIT_FAILURE);
	draw_game(data);
	if (init_minimap(data))
		return (EXIT_FAILURE);
	draw_minimap(data);
	if (init_gameplay(data))
		return (EXIT_FAILURE);
	// draw_gameplay(data, 1);
	mlx_hook(data -> win_ptr, CLOSE, 0, & quit, data);
	mlx_hook(data -> win_ptr, 1, 1UL << 0, & key_hook, data);
	mlx_key_hook(data -> win_ptr, & key_hook, data);
	mlx_loop(data -> mlx_ptr);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	static t_data	data = {0, .player.rotation_angle = M_PI / 2.};
	int				ret;

	if (!env || !*env || ac != 2)
		return (EXIT_FAILURE);
	data.map.filename = av[1];
	ret = parse_map(& data.map);
	if (ret == EXIT_SUCCESS)
	{
		get_playerpos(& data);
		print_map(data);
		lunch_game(& data);
	}
	else
		ft_printf("{blue}-->{yellow}Parsing: {red}%d{reset}\n", ret);
	free_cub3d(& data);
	return (EXIT_SUCCESS);
}
