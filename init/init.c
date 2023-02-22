/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:38:01 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/21 21:25:03 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	init_mlx(t_data *data)
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
	return (EXIT_SUCCESS);
}

int	init_map(t_data *data)
{
	data -> img = mlx_new_image(data -> mlx_ptr, WIDTH, HEIGHT);
	if (!data -> img)
		return (EXIT_FAILURE);
	data -> addr = mlx_get_data_addr(data -> img, & data -> mlx.bits_per_pixel[MLX_IMG_MAP], & data -> mlx.line_length[MLX_IMG_MAP], & data -> mlx.endian);
	if (!data -> addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_minimap(t_data *data)
{
	data -> img_map = mlx_new_image(data -> mlx_ptr, data -> map.width * BLOC_SIZE, data -> map.height * BLOC_SIZE);
	if (!data -> img_map)
		return (EXIT_FAILURE);
	data -> map_addr = mlx_get_data_addr(data -> img_map, & data -> mlx.bits_per_pixel[MLX_IMG_MINIMAP], & data -> mlx.line_length[MLX_IMG_MINIMAP], & data -> mlx.endian);
	if (!data -> map_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int	init_xpm(t_data *data)
{
	int	i;
	int	xy[2];
	const char	*texture[4] = {data->map.path_no, data->map.path_so, data->map.path_we, data->map.path_ea};
	i = 0;
	while (i < 4)
	{
		data -> xpm[i] = mlx_xpm_file_to_image(data -> mlx_ptr, (char *)texture[i], &xy[0], &xy[1]);
		if (!data -> xpm[i])
			return (EXIT_FAILURE);
		data -> xpm_addr[i] = mlx_get_data_addr(data -> xpm[i], & data -> mlx.bits_per_pixel[MLX_IMG_GAME], & data -> mlx.line_length[MLX_IMG_GAME], & data -> mlx.endian);
		if (!data -> xpm_addr[i])
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_gameplay(t_data *data)
{
	data -> img_game = mlx_new_image(data -> mlx_ptr, GAME_WIDTH, GAME_HEIGHT);
	if (!data -> img_game)
		return (EXIT_FAILURE);
	data -> game_addr = mlx_get_data_addr(data -> img_game, & data -> mlx.bits_per_pixel[MLX_IMG_GAME], & data -> mlx.line_length[MLX_IMG_GAME], & data -> mlx.endian);
	if (!data -> game_addr)
		return (EXIT_FAILURE);
	if (!init_xpm(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
