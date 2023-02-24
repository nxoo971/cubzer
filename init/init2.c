/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:22:58 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 03:15:11 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	init_images(t_data *data)
{
	const char	*texture[4] = {data->map.path_no, data->map.path_so, data->map.path_we, data->map.path_ea};
	int			index;
	int			h;
	int			w;

	index = 0;
	while (index < 4)//text siz
	{
		data -> xpm[index] = mlx_xpm_file_to_image(data -> mlx_ptr, (char *)texture[index], & w, & h);
		if (!data -> xpm[index])
			return (ft_printf("{blue}init_images: {red}Failed %s{reset}\n", texture[index]));
		data -> xpm_addr[index] = (int *)mlx_get_data_addr(data -> xpm[index], & data -> mlx.bits_per_pixel[MLX_IMG_SPRITES], & data -> mlx.line_length[MLX_IMG_SPRITES], & data -> mlx.endian);
		if (!data -> xpm_addr[index])
			return (ft_printf("{blue}init_images_addr: {red}Failed %s{reset}\n", texture[index]));
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				data -> texture[index][w * i + j] = ((int *)data -> xpm_addr[index])[w * i + j];
			}
		}
		index++;
	}
	
	return (EXIT_SUCCESS);
}

int	init_buf_texture(t_data *data)
{
	int	i;

	i = -1;
	data -> texture = malloc(sizeof(int *) * TEXTURE_SIZE);
	if (!data -> texture)
		return 0;
	i = -1;
	while (++i < TEXTURE_SIZE)
	{
		data -> texture[i] = ft_calloc(sizeof(int) * (TEXTURE_HEIGHT * TEXTURE_WIDTH), 1);
		if (!data -> texture[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_plane(t_player *player)
{
	player -> plane_x = 0.66 * player -> dir_y;
	player -> plane_y = 0.66 * (player -> dir_x * -1);
	return (EXIT_SUCCESS);
}

int	init_direction(t_data *data)
{
	t_player	*player;
	char		direction;

	player = & data -> player;
	direction = data -> map.map[(int)player -> y][(int)player -> x];
	if (direction == 'N')
	{
		player -> dir_x = 0;
		player -> dir_y = -1;
	}
	else if (direction == 'S')
	{
		player -> dir_x = 0;
		player -> dir_y = 1;
	}
	else if (direction == 'E')
	{
		player -> dir_x = 1;
		player -> dir_y = 0;
	}
	else if (direction == 'W')
	{
		player -> dir_x = -1;
		player -> dir_y = 0;
	}
	return (init_plane(player));
}
