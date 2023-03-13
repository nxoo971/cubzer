/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/13 18:51:18 by rferradi         ###   ########.fr       */
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
int	launch_game(t_data *data)
{
	if (init_mlx(data))
		return (EXIT_FAILURE);
	if (init_map(data))
		return (EXIT_FAILURE);
	if (init_minimap(data))
		return (EXIT_FAILURE);
	if (init_gameplay(data))
		return (EXIT_FAILURE);
	if (init_direction(& data -> params, data -> player.p))
		return (EXIT_FAILURE);
	if (init_buf_texture(data))
		return (EXIT_FAILURE);
	if (init_images(data))
		return (EXIT_FAILURE);
	data->mouse = WIDTH/2;
	data->mousebool = 0;
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, (void *)data);
	mlx_hook(data->win_ptr, 2, 1UL << 0, & key_press, data);
	mlx_hook(data->win_ptr, 3, 1UL << 1, & key_release, data);
	mlx_loop_hook(data -> mlx_ptr, & key_hook, data);
	mlx_loop(data -> mlx_ptr);
	return (0);
}

void	stock_door(char **map, t_map *m)
{
	int	i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D')
			{
				printf("door found at %d %d\n", i, j);
				m->door.y = i;
				m->door.x = j;
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	static t_data	data = {0};
	static t_player	player = {0};
	int				ret;

	if (!env || !*env || ac != 2)
		return (EXIT_FAILURE);
	data.map.filename = av[1];
	ret = parse_map(& data.map, & player) + malloc_sprite(&data);
	if (ret == EXIT_SUCCESS)
	{
		data.player = player;
		print_map(data);
		stock_door(data.map.map, &data.map);
		launch_game(& data);
	}
	else
		ft_printf("{blue}-->{yellow}Parsing: {red}%d{reset}\n", ret);
	free_cub3d(& data);
	return (EXIT_SUCCESS);
}
