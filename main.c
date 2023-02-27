/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/27 04:15:45 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./includes/cub3d.h"

void	mlx_put_pixel(t_mlx mlx, int y, int x, int color)
{
	char	*dst;

	dst = mlx.addr + (y * mlx.line_length[mlx.index] \
						+ x * (mlx.bits_per_pixel[mlx.index] / 8));
	*(unsigned int *)dst = color;
}

static
int	launch_game(t_data *data)
{
	if (init_mlx(data))
		return (EXIT_FAILURE);
	if (init_map(data))
		return (EXIT_FAILURE);
	if (init_direction(& data -> params, data -> player.p))
		return (EXIT_FAILURE);
	if (init_buf_texture(data))
		return (EXIT_FAILURE);
	if (init_images(data))
		return (EXIT_FAILURE);
	mlx_hook(data->win_ptr, 2, 1UL << 0, & key_press, data);
	mlx_hook(data->win_ptr, 3, 1UL << 1, & key_release, data);
	mlx_loop_hook(data -> mlx_ptr, & key_hook, data);
	mlx_loop(data -> mlx_ptr);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	static t_data	data = {0};
	static t_player	player = {.y = -1, .x = -1};
	int				ret;

	if (!env || !*env || ac != 2)
		return (EXIT_FAILURE);
	data.map.filename = av[1];
	ret = parse_map(& data.map, & player);
	if (ret == EXIT_SUCCESS)
	{
		data.player = player;
		launch_game(& data);
	}
	else
		ft_printf("{blue}-->{yellow}Parsing: {red}FAILED{reset}\n");
	free_cub3d(& data);
	return (EXIT_SUCCESS);
}
