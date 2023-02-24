/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 07:50:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 19:12:46 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	key_hook(t_data *data)
{
	t_player	*p;

	p = & data -> player;
	if (data -> press.esc)
		mlx_loop_end(data -> mlx_ptr);
	if (data -> press.w)
		move_player(data, +1, +1);
	if (data -> press.a)
		move_player_side(data, -1, +1);
	if (data -> press.s)
		move_player(data, -1, -1);
	if (data -> press.d)
		move_player_side(data, +1, -1);
	if (data -> press.left)
		move_angle(data, +1);
	if (data -> press.right)
		move_angle(data, -1);
	draw_gameplay(data);
	mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr, data->img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		exit(0);
	if (keycode == W)
		data -> press.w = keycode;
	if (keycode == A)
		data -> press.a = keycode;
	if (keycode == S)
		data -> press.s = keycode;
	if (keycode == D)
		data -> press.d = keycode;
	if (keycode == LEFT)
		data -> press.left = keycode;
	if (keycode == RIGHT)
		data -> press.right = keycode;
	if (keycode == ESC)
		data -> press.esc = keycode;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	int *const	start = & data -> press.w;
	int			i;

	i = -1;
	while (++i < TPRESS_SIZE)
	{
		if (*(start + i) == keycode)
			*(start + i) = false;
	}
	return (0);
}
