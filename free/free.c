/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:47:36 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/14 19:15:49 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

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
	if (data -> img_map)
		mlx_destroy_image(data -> mlx_ptr, data -> img_map);
	if (data -> img_game)
		mlx_destroy_image(data -> mlx_ptr, data -> img_game);
	int i = -1;
	for (; ++i < TEXTURE_SIZE && data -> xpm[i];)
		mlx_destroy_image(data -> mlx_ptr, data -> xpm[i]);
	for (int i = 0; i < HEIGHT; i++)
		free(data -> buf[i]);
	for (int i = 0; i < TEXTURE_SIZE && data -> texture[i]; i++)
		free(data -> texture[i]);
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
