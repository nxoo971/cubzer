/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:38:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/17 18:50:22 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void bresenham_line(t_mlx mlx, int x0, int y0, int x1, int y1)
{
    int	dx;
    int	sx;
    int	dy;
    int	sy;
    int	err;
    int	e2;
	
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_put_pixel(mlx, x0, y0, 0xF14457);    
		if (x0 == x1 && y0 == y1) 
			break;
		e2 = 2 * err;
		if (e2 >= dy) 
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) 
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	bresenham_circle(t_mlx mlx, int xc, int yc, int r)
{
	int x;
	int y;
	int d;
	
	x = 0;
	y = r;
	d = r - 1;
	while (y >= x)
	{
		mlx_put_pixel(mlx, xc + x, yc + y, 0xFFFFFF);
		mlx_put_pixel(mlx, xc + y, yc + x, 0xFFFFFF);
		mlx_put_pixel(mlx, xc - x, yc + y, 0xFFFFFF);
		mlx_put_pixel(mlx, xc - y, yc + x, 0xFFFFFF);
		mlx_put_pixel(mlx, xc - x, yc - y, 0xFFFFFF);
		mlx_put_pixel(mlx, xc - y, yc - x, 0xFFFFFF);
		mlx_put_pixel(mlx, xc + x, yc - y, 0xFFFFFF);
		mlx_put_pixel(mlx, xc + y, yc - x, 0xFFFFFF);
		if (d >= 2 * x)
		{
			d -= 2 * x + 1;
			x++;
		}
		else if (d < 2 * (r - y))
		{
			d += 2 * y - 1;
			y--;
		}
		else
		{
			d += 2 * (y - x - 1);
			y--;
			x++;
		}
	}
}
