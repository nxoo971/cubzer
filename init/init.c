/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:38:01 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/27 03:01:19 by jewancti         ###   ########.fr       */
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
	data -> addr = mlx_get_data_addr(data -> img,
			& data -> mlx.bits_per_pixel[MLX_IMG_MAP],
			& data -> mlx.line_length[MLX_IMG_MAP],
			& data -> mlx.endian);
	if (!data -> addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
