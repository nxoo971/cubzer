/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/10 19:18:10 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./includes/cub3d.h"

void	mlx_put_pixel(t_mlx mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx.addr + (y * mlx.line_length + x * (mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static
void	testgetp(t_data *data)
{
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
		move_vertical(data, - 1);
	if (keycode == DOWN || keycode == S)
		move_vertical(data, + 1);
	if (keycode == LEFT || keycode == A)
		move_horizontal(data, - 1);
	if (keycode == RIGHT || keycode == D)
		move_horizontal(data, + 1);
	draw_map(data);
	//print_map(*data);
	return (0);
}

static
int	lunch_game(t_data *data)
{
	data -> mlx_ptr = mlx_init();
	if (!data -> mlx_ptr)
		return (EXIT_FAILURE);
	data -> win_ptr = mlx_new_window(data -> mlx_ptr, WIDTH, HEIGHT, "CubZer");
	if (!data -> win_ptr)
	{
		free(data -> mlx_ptr);
		return (EXIT_FAILURE);
	}
	draw(data);
	mlx_hook(data -> win_ptr, CLOSE, 0, & quit, data);
	mlx_hook(data -> win_ptr, 1, 1UL << 0, & key_hook, data);
	mlx_key_hook(data -> win_ptr, & key_hook, data);
	mlx_loop(data -> mlx_ptr);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	static t_data	data = {0};
	int				ret;

	if (!env || !*env || ac != 2)
		return (EXIT_FAILURE);
	data.map.filename = av[1];
	ret = parse_map(& data.map);
	if (ret == EXIT_SUCCESS)
	{
		testgetp(& data);
		print_map(data);
		//lunch_game(& data);
		start_game(& data);
	}
	else
		ft_printf("{blue}-->{yellow}Parsing: {red}%d{reset}\n", ret);
	free_cub3d(& data);
	return (EXIT_SUCCESS);
}
