/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:47:36 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/08 05:19:26 by jewancti         ###   ########.fr       */
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
	mlx_destroy_image(data -> mlx_ptr, data -> img);
	mlx_destroy_image(data -> mlx_ptr, data -> img_map);
	mlx_clear_window(data -> mlx_ptr, data -> win_ptr);
	mlx_destroy_window(data -> mlx_ptr, data -> win_ptr);
	mlx_destroy_display(data -> mlx_ptr);
	free(data -> mlx_ptr);
}
