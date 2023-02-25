/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:22:58 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/25 05:07:39 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
void	set_textures(int *texture, const void *xpm_addr, const int height, const int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			texture[width * i + j] = ((int *)xpm_addr)[width * i + j];
	}
}

int	init_images(t_data *data)
{
	const char	*path_textures[TEXTURE_SIZE] = {
		data -> map.path_no, data -> map.path_so, data -> map.path_we, data -> map.path_ea
	};
	int			index;
	int			h;
	int			w;

	index = 0;
	while (index < TEXTURE_SIZE)
	{
		data -> xpm[index] = mlx_xpm_file_to_image(data -> mlx_ptr, (char *)path_textures[index], & w, & h);
		if (!data -> xpm[index])
			return (ft_printf("{blue}init_images: {red}Failed %s{reset}\n", path_textures[index]));
		data -> xpm_addr[index] = (int *)mlx_get_data_addr(data -> xpm[index], & data -> mlx.bits_per_pixel[MLX_IMG_SPRITES], & data -> mlx.line_length[MLX_IMG_SPRITES], & data -> mlx.endian);
		if (!data -> xpm_addr[index])
			return (ft_printf("{blue}init_images_addr: {red}Failed %s{reset}\n", path_textures[index]));
		set_textures(data -> texture[index], data -> xpm_addr[index], h, w);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	init_buf_texture(t_data *data)
{
	int	i;

	i = -1;
	while (++i < HEIGHT)
	{
		data -> buf[i] = ft_calloc(sizeof(int) * WIDTH, 1);
		if (!data -> buf[i])
			return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < TEXTURE_SIZE)
	{
		data -> texture[i] = ft_calloc(sizeof(int) * (TEXTURE_HEIGHT * TEXTURE_WIDTH), 1);
		if (!data -> texture[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_plane(t_params *params)
{
	params -> plane_x = 0.66 * params -> dir_y;
	params -> plane_y = 0.66 * (params -> dir_x * -1);
	return (EXIT_SUCCESS);
}

int	init_direction(t_params *params, const char spawn_direction)
{
	if (spawn_direction == 'N')
	{
		params -> dir_x = 0;
		params -> dir_y = -1;
	}
	else if (spawn_direction == 'S')
	{
		params -> dir_x = 0;
		params -> dir_y = 1;
	}
	else if (spawn_direction == 'E')
	{
		params -> dir_x = 1;
		params -> dir_y = 0;
	}
	else if (spawn_direction == 'W')
	{
		params -> dir_x = -1;
		params -> dir_y = 0;
	}
	return (init_plane(params));
}
