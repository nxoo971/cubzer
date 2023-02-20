/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:50:08 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/20 06:47:58 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"
#include <stdio.h>

//void	print_map(const t_map map)
//{
//	ft_printf("{green}Window size: {reset}\n");
//	ft_printf("{magenta}\tHeight: {cyan}%d{reset}\n", map.height);
//	ft_printf("{magenta}\tWidth: {cyan}%d{reset}\n", map.width);
//	ft_printf("\n");
//	ft_printf("{green}Textures: {reset}\n");
//	ft_printf("{magenta}\tNO: {cyan}%d{reset}\n", map.no_is_defined);
//	ft_printf("{magenta}\tNO path: {cyan}%s{reset}\n", map.path_no);
//	ft_printf("\n");
//	ft_printf("{magenta}\tSO: {cyan}%d{reset}\n", map.so_is_defined);
//	ft_printf("{magenta}\tSO path: {cyan}%s{reset}\n", map.path_so);
//	ft_printf("\n");
//	ft_printf("{magenta}\tWE: {cyan}%d{reset}\n", map.we_is_defined);
//	ft_printf("{magenta}\tWE path: {cyan}%s{reset}\n", map.path_we);
//	ft_printf("\n");
//	ft_printf("{magenta}\tEA: {cyan}%d{reset}\n", map.ea_is_defined);
//	ft_printf("{magenta}\tEA path: {cyan}%s{reset}\n", map.path_ea);
//	ft_printf("\n");
//	ft_printf("{magenta}\tFloor: {cyan}%d{reset}\n", map.floor_is_defined);
//	ft_printf("{magenta}\tFloor color: {cyan}[%d:%d:%d]{reset}\n", map.color_floor[0], map.color_floor[1], map.color_floor[2]);
//	ft_printf("\n");
//	ft_printf("{magenta}\tCEIL: {cyan}%d{reset}\n", map.ceil_is_defined);
//	ft_printf("{magenta}\tCEIL color: {cyan}[%d:%d:%d]{reset}\n", map.color_ceil[0], map.color_ceil[1], map.color_ceil[2]);
//	ft_printf("\n");
//	ft_printf("\n");
//	ft_printf("{green}MAP: {reset}\n");
//	for (int i = 0; map.map && map.map[i]; i++)
//		ft_printf("{yellow}%s{reset}\n", map.map[i]);
//	//ft_printmap(map . map, 0);
//	//ft_printmap(map . map, 1);
//	//ft_displaydouble(map . map);
//}

void	print_map(const t_data data)
{
	// ft_printf("{green}Window size: {reset}\n");
	// ft_printf("{magenta}\tHeight: {cyan}%d{reset}", data.map.height);
	// ft_printf("{magenta}\tWidth: {cyan}%d{reset}\n", data.map.width);
	// ft_printf("\n");
	// ft_printf("{green}Textures: {reset}\n");
	// ft_printf("{magenta}\tNO: {cyan}%d{reset}", data.map.no_is_defined);
	// ft_printf("{magenta}\t\tSO: {cyan}%d{reset}\n", data.map.so_is_defined);
	// ft_printf("{magenta}\tWE: {cyan}%d{reset}", data.map.we_is_defined);
	// ft_printf("{magenta}\t\tEA: {cyan}%d{reset}\n\n", data.map.ea_is_defined);

	// ft_printf("{magenta}\tNO path: {cyan}%s{reset}", data.map.path_no);
	// ft_printf("{magenta}\tSO path: {cyan}%s{reset}\n", data.map.path_so);
	// ft_printf("{magenta}\tWE path: {cyan}%s{reset}", data.map.path_we);
	// ft_printf("{magenta}\tEA path: {cyan}%s{reset}\n\n", data.map.path_ea);

	// ft_printf("{magenta}\tFloor: {cyan}%d{reset}\n", data.map.floor_is_defined);
	// ft_printf("{magenta}\tFloor color: {cyan}[%d:%d:%d]{reset}\n", data.map.color_floor[0], data.map.color_floor[1], data.map.color_floor[2]);
	// ft_printf("\n");
	// ft_printf("{magenta}\tCEIL: {cyan}%d{reset}\n", data.map.ceil_is_defined);
	// ft_printf("{magenta}\tCEIL color: {cyan}[%d:%d:%d]{reset}\n", data.map.color_ceil[0], data.map.color_ceil[1], data.map.color_ceil[2]);
	// ft_printf("\n");
	ft_printf("{green}PLAYER: {reset}\n");
		printf("y: %f\n", data.player.y);
		printf("x: %f\n", data.player.x);
	ft_printf("\n");
	// ft_printf("\n");
	// ft_printf("\n");
	//ft_printf("{green}MAP: {reset}\n");
	//for (int i = 0; data.map.map && data.map.map[i]; i++)
	//	ft_printf("{yellow}%s{reset}\n", data.map.map[i]);
	//ft_printmap(map . map, 0);
	//ft_printmap(map . map, 1);
	//ft_displaydouble(map . map);
}