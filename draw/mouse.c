/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:57 by rferradi          #+#    #+#             */
/*   Updated: 2023/03/14 16:53:29 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int   mouse_move(int sign_y, int sign_x, void *data)
{
    t_data *d;

    d = (t_data *)data;
    int middle = WIDTH/2;
    if (sign_y == middle)
        return (0);
    if (d->mouse > sign_y)
        move_angle(d, +1);
    else
        move_angle(d, -1);
    d->mouse = sign_y;
    return (1);
}   