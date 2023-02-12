/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:50:08 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/11 23:01:09 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"
#include <stdio.h>

# define SPACES " \t"
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

char	*colored(char *str, int value)
{
	int i = 0;

	while(str[i] && value)
	{
		if (str[i] == '1')
			printf("%s%c%s", "\033[7;35m", ' ', RESET);
		if (str[i] == '0')
			printf("%s%c%s", "\033[7;32m", ' ', RESET);
		if (str[i] == ' ')
			printf("%s%c%s", "\033[7;33m", ' ', RESET);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W') 
			printf("%s%c%s", "\033[7;32m", str[i], RESET);
		if (str[i] == 'R')
			printf("%s%c%s", "\033[7;31m", ' ', RESET);
		i++;
	}
	while(str[i] && !value)
	{
		if (str[i] == '1')
			printf("%s%c%s", MAGENTA, str[i], RESET);
		if (str[i] == '0')
			printf("%s%c%s", "\033[7;32m", str[i], RESET);
		if (str[i] == ' ')
			printf("%s%c%s", "\033[7;33m", str[i], RESET);
		if (str[i] == 'R')
			printf("%s%c%s", "\033[7;31m", ' ', RESET);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W') 
			printf("%s%c%s", WHITE, str[i], RESET);
		i++;
	}
	return (NULL);
	

}

void	ft_printmap(char **tab, int value)
{
	int	i;
	int	j;
	int	size;
	int	max;
	int	var;
	int	temp;

	static char *color[6] = {
		YELLOW, RED, GREEN, CYAN, BLUE, MAGENTA};
	var = 0;
	i = -1;
	j = -1;
	size = -1;
	max = 0;
	printf("\t\tMAP %i\n", value);
	while (tab[++size])
	{
		i = ft_strlen(tab[size]);
		if (i > max)
			max = i;
	}
	temp = max;
	printf(" ");
	while (++j < max)
	{
		printf("%s%i%s", color[var], j, RESET);
		if (j == 9)
		{
			if (var++ == 5)
				var = 0;
			j = -1;
			max -= 10;
		}
	}
	printf("\n");
	i = -1;
	j = 0;
	var = 0;
	while (tab[++i])
	{
		int val = ft_strlen(tab[i]);
		if (val == temp)
		{
			printf("%s%i%s", color[var], j, RESET);
			colored(tab[i], value);
			printf("%s%i%s\n", color[var], j, RESET);
		}
		else
		{
			printf("%s%i%s\n", color[var], j, RESET);
			colored(tab[i], value);
			printf("%*c%s%i%s\n", temp - (int)ft_strlen(tab[i]), ' ', color[var], j, RESET);
		}
		if (j++ == 9)
		{
			if (var++ == 5)
				var = 0;
			j = 0;
		}
	}
	printf(" ");
	j = -1;
	var = 0;
	max = temp;
	while (++j < max)
	{
		printf("%s%i%s", color[var], j, RESET);
		if (j == 9)
		{
			if (var++ == 5)
				var = 0;
			j = -1;
			max -= 10;
		}
	}
	printf("\n");
}

char	*c(int n)
{
	int len;
	static char *color[6] = {
		YELLOW, RED, GREEN, CYAN, BLUE, MAGENTA};

	len = 0;
	while (n > 10)
	{
		n /= 10;
		if (len++ == 5)
			len = 0;
	}
	return (color[len]);
}

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
	ft_printf("{green}Window size: {reset}\n");
	ft_printf("{magenta}\tHeight: {cyan}%d{reset}", data.map.height);
	ft_printf("{magenta}\tWidth: {cyan}%d{reset}\n", data.map.width);
	ft_printf("\n");
	ft_printf("{green}Textures: {reset}\n");
	ft_printf("{magenta}\tNO: {cyan}%d{reset}", data.map.no_is_defined);
	ft_printf("{magenta}\t\tSO: {cyan}%d{reset}\n", data.map.so_is_defined);
	ft_printf("{magenta}\tWE: {cyan}%d{reset}", data.map.we_is_defined);
	ft_printf("{magenta}\t\tEA: {cyan}%d{reset}\n\n", data.map.ea_is_defined);

	ft_printf("{magenta}\tNO path: {cyan}%s{reset}", data.map.path_no);
	ft_printf("{magenta}\tSO path: {cyan}%s{reset}\n", data.map.path_so);
	ft_printf("{magenta}\tWE path: {cyan}%s{reset}", data.map.path_we);
	ft_printf("{magenta}\tEA path: {cyan}%s{reset}\n\n", data.map.path_ea);

	ft_printf("{magenta}\tFloor: {cyan}%d{reset}\n", data.map.floor_is_defined);
	ft_printf("{magenta}\tFloor color: {cyan}[%d:%d:%d]{reset}\n", data.map.color_floor[0], data.map.color_floor[1], data.map.color_floor[2]);
	ft_printf("\n");
	ft_printf("{magenta}\tCEIL: {cyan}%d{reset}\n", data.map.ceil_is_defined);
	ft_printf("{magenta}\tCEIL color: {cyan}[%d:%d:%d]{reset}\n", data.map.color_ceil[0], data.map.color_ceil[1], data.map.color_ceil[2]);
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("{green}MAP: {reset}\n");
	for (int i = 0; data.map.map && data.map.map[i]; i++)
		ft_printf("{yellow}%s{reset}\n", data.map.map[i]);
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("{green}PLAYER: {reset}\n");
		ft_printf("{yellow}y: %d{reset}\n", data.player.y);
		ft_printf("{yellow}x: %d{reset}\n", data.player.x);
	//ft_printmap(map . map, 0);
	//ft_printmap(map . map, 1);
	//ft_displaydouble(map . map);
}