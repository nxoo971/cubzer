/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:47:36 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/14 23:21:15 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static
void	free_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEXTURE_SIZE && data -> xpm[i])
		mlx_destroy_image(data -> mlx_ptr, data -> xpm[i]);
	i = -1;
	while (++i < HEIGHT)
		free(data -> buf[i]);
	i = -1;
	while (++i < TEXTURE_SIZE && data -> texture[i])
		free(data -> texture[i]);
}

void	free_cub3d(t_data *data)
{
	ft_arraydel(data -> map.map);
	ft_memdel((void **)& data -> map.path_so);
	ft_memdel((void **)& data -> map.path_no);
	ft_memdel((void **)& data -> map.path_we);
	ft_memdel((void **)& data -> map.path_ea);
	ft_memdel((void **)& data -> map.door);
	if (data -> img)
		mlx_destroy_image(data -> mlx_ptr, data -> img);
	free_textures(data);
	if (data -> mlx_ptr)
	{
		if (data -> win_ptr)
		{
			mlx_clear_window(data -> mlx_ptr, data -> win_ptr);
			mlx_destroy_window(data -> mlx_ptr, data -> win_ptr);
		}
		mlx_destroy_display(data -> mlx_ptr);
		free(data -> mlx_ptr);
	}
}
