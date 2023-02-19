/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/19 23:39:56 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./includes/cub3d.h"

void	mlx_put_pixel(t_mlx mlx, int y, int x, int color)
{
	char	*dst;

	dst = mlx.addr + (y * mlx.line_length[mlx.index] + x * (mlx.bits_per_pixel[mlx.index] / 8));
	*(unsigned int *)dst = color;
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
	t_player	*p;
	double		old_dir_y;
	double 		old_plane_y;

	p = & data -> player;
	if (keycode == ESC)
		mlx_loop_end(data -> mlx_ptr);
	if (keycode == W)
	{
		if (data -> map.map[(int)(p -> y)][(int)((p -> x + p -> dir_x * MOVE_SPEED))] != WALL)
			p -> x += p -> dir_x * MOVE_SPEED;
		if (data -> map.map[(int)(p -> y + p->dir_y * MOVE_SPEED)][(int)((p -> x))] != WALL)
			p -> y += p -> dir_y * MOVE_SPEED;
	}
	if (keycode == S)
	{
		if(data -> map.map[(int)(p -> y)][(int)(p -> x - p -> dir_x * MOVE_SPEED)] != WALL)
			p -> x -= p -> dir_x * MOVE_SPEED;
		if(data -> map.map[(int)(p -> y - p -> dir_y * MOVE_SPEED)][(int)(p -> x)] != WALL)
			p -> y -= p -> dir_y * MOVE_SPEED;
	}
	if (keycode == LEFT)
	{
		double oldir = p->dir_x;
		p->dir_x = p->dir_x * cos(ROTATION_SPEED) - p->dir_y * sin(ROTATION_SPEED);
		p->dir_y = oldir * sin(ROTATION_SPEED) + p->dir_y * cos(ROTATION_SPEED);
		double oldplane = p->plane_x;
		p->plane_x = p->plane_x * cos(ROTATION_SPEED) - p->plane_y * sin(ROTATION_SPEED);
		p->plane_y = oldplane * sin(ROTATION_SPEED) + p->plane_y * cos(ROTATION_SPEED);
	}
	if (keycode == RIGHT)
	{
		double oldir = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROTATION_SPEED) - p->dir_y * sin(-ROTATION_SPEED);
		p->dir_y = oldir * sin(-ROTATION_SPEED) + p->dir_y * cos(-ROTATION_SPEED);
		double oldplane = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROTATION_SPEED) - p->plane_y * sin(-ROTATION_SPEED);
		p->plane_y = oldplane * sin(-ROTATION_SPEED) + p->plane_y * cos(-ROTATION_SPEED);
	}
	if (keycode == 'd')
	{
		if (data -> map.map[(int)(p -> y)][(int)((p -> x + p -> dir_y * MOVE_SPEED))] != WALL)
			p -> x += p -> dir_y * MOVE_SPEED;
		if (data -> map.map[(int)(p -> y - p->dir_x * MOVE_SPEED)][(int)((p -> x))] != WALL)
			p -> y -= p -> dir_x * MOVE_SPEED;
	}
	if (keycode == 'a')
	{
		if (data -> map.map[(int)(p -> y)][(int)((p -> x - p -> dir_y * MOVE_SPEED))] != WALL)
			p -> x -= p -> dir_y * MOVE_SPEED;
		if (data -> map.map[(int)(p -> y + p->dir_x * MOVE_SPEED)][(int)((p -> x))] != WALL)
			p -> y += p -> dir_x * MOVE_SPEED;
	}
	// if (keycode == 'a')
	// {
	// 	if (data -> map.map[(int)(p -> y)][(int)(p -> x + MOVE_SPEED)] != WALL)
	// 		p -> x += MOVE_SPEED * p->dir_x;
	// 	if (data -> map.map[(int)(p -> y - p -> plane_y * MOVE_SPEED)][(int)(p -> x)] != WALL)
	// 		p -> y -= p -> plane_y * MOVE_SPEED;
	// }
	// if (keycode == 'd')
	// {
	// 	if (data -> map.map[(int)(p -> y)][(int)(p -> x - MOVE_SPEED)] != WALL)
	// 		p -> x -= MOVE_SPEED;
	// }
	// print_map(*data);
	draw_gameplay(data);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> img, 0, 0);
	return (0);
}

// ya heja quand tu rentre dans un mur tu peux plus ressortir mais je crois faut utiliser
// floor pour arrondir en dessous et etre sur de pas toucher le mur

static
int	launch_game(t_data *data)
{
	// jai init a l'arache t'avais oublier c pour les direction quand tu tourne
	// data->player.dir_x = -1;
	// data->player.dir_y = 0;
	// data->player.plane_x = 0;
	// data->player.plane_y = 0.66;
	if (init_mlx(data))
		return (EXIT_FAILURE);
	if (init_map(data))
		return (EXIT_FAILURE);
	if (init_minimap(data))
		return (EXIT_FAILURE);
	if (init_gameplay(data))
		return (EXIT_FAILURE);
	//draw_game(data);
	draw_gameplay(data);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> img, 0, 0);
	mlx_hook(data -> win_ptr, CLOSE, 0, & quit, data);
	mlx_hook(data -> win_ptr, 1, 1UL << 0, & key_hook, data);
	mlx_key_hook(data -> win_ptr, & key_hook, data);
	mlx_loop(data -> mlx_ptr);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	//static int		spawn_direction[4] = {0};
	static t_data	data = {0};
	static t_player	player = {0, .dir_x = -1, .dir_y = 0,
								.plane_x = 0, .plane_y = 0.66};
	int				ret;

	if (!env || !*env || ac != 2)
		return (EXIT_FAILURE);
	data.map.filename = av[1];
	ret = parse_map(& data.map, & player);
	if (ret == EXIT_SUCCESS)
	{
		data.player = player;
		print_map(data);
		launch_game(& data);
	}
	else
		ft_printf("{blue}-->{yellow}Parsing: {red}%d{reset}\n", ret);
	free_cub3d(& data);
	return (EXIT_SUCCESS);
}
