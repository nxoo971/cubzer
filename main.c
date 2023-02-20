/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/20 01:46:19 by rferradi         ###   ########.fr       */
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
int	key_hook(t_data *data)
{
	t_player	*p;
	double		old_dir_y;
	double 		old_plane_y;

	p = & data -> player;
	if (data->press.esc == 1)
		mlx_loop_end(data -> mlx_ptr);
	if (data->press.w == 1)
	{
		if (data -> map.map[(int)(p -> y)][(int)((p -> x + p -> dir_x * MOVE_SPEED))] != WALL)
			p -> x += p -> dir_x * MOVE_SPEED;
		if (data -> map.map[(int)(p -> y + p->dir_y * MOVE_SPEED)][(int)((p -> x))] != WALL)
			p -> y += p -> dir_y * MOVE_SPEED;
	}
	if (data->press.s == 1)
	{
		if(data -> map.map[(int)(p -> y)][(int)(p -> x - p -> dir_x * MOVE_SPEED)] != WALL)
			p -> x -= p -> dir_x * MOVE_SPEED;
		if(data -> map.map[(int)(p -> y - p -> dir_y * MOVE_SPEED)][(int)(p -> x)] != WALL)
			p -> y -= p -> dir_y * MOVE_SPEED;
	}
	if (data->press.left == 1)
	{
		double oldir = p->dir_x;
		p->dir_x = p->dir_x * cos(ROTATION_SPEED) - p->dir_y * sin(ROTATION_SPEED);
		p->dir_y = oldir * sin(ROTATION_SPEED) + p->dir_y * cos(ROTATION_SPEED);
		double oldplane = p->plane_x;
		p->plane_x = p->plane_x * cos(ROTATION_SPEED) - p->plane_y * sin(ROTATION_SPEED);
		p->plane_y = oldplane * sin(ROTATION_SPEED) + p->plane_y * cos(ROTATION_SPEED);
	}
	if (data->press.right == 1)
	{
		double oldir = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROTATION_SPEED) - p->dir_y * sin(-ROTATION_SPEED);
		p->dir_y = oldir * sin(-ROTATION_SPEED) + p->dir_y * cos(-ROTATION_SPEED);
		double oldplane = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROTATION_SPEED) - p->plane_y * sin(-ROTATION_SPEED);
		p->plane_y = oldplane * sin(-ROTATION_SPEED) + p->plane_y * cos(-ROTATION_SPEED);
	}
	if (data->press.d == 1)
	{
		if (data -> map.map[(int)(p -> y)][(int)((p -> x + p -> dir_y * MOVE_SPEED))] != WALL)
			p -> x += p -> dir_y * MOVE_SPEED;
		if (data -> map.map[(int)(p -> y - p->dir_x * MOVE_SPEED)][(int)((p -> x))] != WALL)
			p -> y -= p -> dir_x * MOVE_SPEED;
	}
	if (data->press.a == 1)
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

int key_press(int key, t_data *data)
{
	printf("key = %d\n", key);
	if (key == 53)
		exit(0);
	if (key == 'w')
		data->press.w = 1;
	if (key == 's')
		data->press.s= 1;
	if (key == 'a')
		data->press.a = 1;
	if (key == 'd')
		data->press.d = 1;
	if (key == 65361)
		data->press.left = 1;
	if (key == 65363)
		data->press.right = 1;
	if (key == ESC)
		data->press.esc = 1;
	return (0);
}

int key_release(int key, t_data *data)
{
	if (key == 'w')
		data->press.w = 0;
	if (key == 's')
		data->press.s= 0;
	if (key == 'a')
		data->press.a = 0;
	if (key == 'd')
		data->press.d = 0;
	if (key == 65361)
		data->press.left = 0;
	if (key == 65363)
		data->press.right = 0;
	if (key == ESC)
		data->press.esc = 0;
	return (0);
}


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
	mlx_hook(data->win_ptr, 2, 1UL<<0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1UL<<1, key_release, data);
	mlx_loop_hook(data -> mlx_ptr, & key_hook, data);
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
