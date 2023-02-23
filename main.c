/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/23 19:10:32 by rferradi         ###   ########.fr       */
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
	load_texture(data);
	
	//draw_game(data);
	
	// mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data -> img, 0, 0);
	//draw_gameplay(data);
	mlx_hook(data -> win_ptr, CLOSE, 0, & quit, data);
	mlx_hook(data -> win_ptr, 1, 1UL << 0, & key_hook, data);
	mlx_key_hook(data -> win_ptr, & key_hook, data);
	// mlx_hook(data->win_ptr, 2, 1UL<<0, key_press, data);
	// mlx_hook(data->win_ptr, 3, 1UL<<1, key_release, data);
	// mlx_loop_hook(data -> mlx_ptr, & key_hook, data);
	mlx_loop(data -> mlx_ptr);
	return (0);
}

void	init_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player -> dir_x = 0;
		player -> dir_y = -1;
		
	}
	else if (dir == 'S')
	{
		player -> dir_x = 0;
		player -> dir_y = 1;
	}
	else if (dir == 'E')
	{
		player -> dir_x = 1;
		player -> dir_y = 0;
	}
	else if (dir == 'W')
	{
		player -> dir_x = -1;
		player -> dir_y = 0;
	}
	player->plane_x = 0.66 * player->dir_y ;
	player->plane_y = 0.66 * (-1 *player->dir_x) ;
}

int	main(int ac, char **av, char **env)
{
	//static int		spawn_direction[4] = {0};
	static t_data	data = {0};
	static t_player	player = {0, .dir_x = 0, .dir_y = -1};

	int				ret;
	
	if (!env || !*env || ac != 2)
		return (EXIT_FAILURE);
	data.map.filename = av[1];
	ret = parse_map(& data.map, & player);
	if (ret == EXIT_SUCCESS)
	{
		data.player = player;
		init_dir(& data.player, 'W');
		print_map(data);
		data.buf = malloc(sizeof(int *) * HEIGHT);
		for (int i = 0; i < HEIGHT; i++)
		{
			data.buf[i] = malloc(sizeof(int) * WIDTH);
			for (int j = 0; j < WIDTH; j++)
			{
				data.buf[i][j] = 0;
			}
		}
		if (!(data.texture = (int **)malloc(sizeof(int *) * 8)))
			return 0;
		for (int i = 0; i < 8; i++)
		{
			if (!(data.texture[i] = (int *)malloc(sizeof(int) * (textheight * textwidth))))
				return 0;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < textheight * textwidth; j++)
			{
				data.texture[i][j] = 0;
			}
		}
		
		launch_game(& data);
	}
	else
		ft_printf("{blue}-->{yellow}Parsing: {red}%d{reset}\n", ret);
	free_cub3d(& data);
	return (EXIT_SUCCESS);
}
