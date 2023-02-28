/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:48:11 by rferradi          #+#    #+#             */
/*   Updated: 2023/02/27 23:38:29 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

t_sprite sprite[numSprites] =
	{
		// {20.5, 11.5, 10}, // green light in front of playerstart
		// // green lights in every room
		// {18.5, 4.5, 10},
		// {10.0, 4.5, 10},
		// {10.0, 12.5, 10},
		// {3.5, 6.5, 10},
		// {3.5, 20.5, 10},
		// {3.5, 14.5, 10},
		// {14.5, 20.5, 10},

		// // row of pillars in front of wall: fisheye test
		// {18.5, 10.5, 9},
		// {18.5, 11.5, 9},
		// {18.5, 12.5, 9},

		// // some barrels around the map
		{4, 5, 7},
		{4, 4, 8},
		// {16.0, 1.8, 8},
		// {16.2, 1.2, 8},
		// {3.5, 2.5, 8},
		// {9.5, 15.5, 8},
		// {10.0, 15.1, 8},
		// {10.5, 15.8, 8},
};


void sort_order(t_pair *orders, int amount)
{
	t_pair tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void sortSprites(int *order, double *dist, int amount)
{
	t_pair *sprites;

	// std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	// std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void begin_sprite(t_data *data, t_player *player, t_params *params)
{
	for (int i = 0; i < numSprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((player->x - sprite[i].x) * (player->x - sprite[i].x) + (player->y - sprite[i].y) * (player->y - sprite[i].y)); // sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);
	// after sorting the sprites, do the projection and draw them
	for (int i = 0; i < numSprites; i++)
	{
		// translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - player->x;
		double spriteY = sprite[spriteOrder[i]].y - player->y;

		// transform sprite with the inverse camera matrix
		//  [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		//  [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		//  [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (params->plane_x * params->dir_y - params->dir_x * params->plane_y); // required for correct matrix multiplication

		double transformX = invDet * (params->dir_y * spriteX - params->dir_x * spriteY);
		double transformY = invDet * (-params->plane_y * spriteX + params->plane_x * spriteY); // this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

// parameters for scaling and moving the sprites
#define uDiv 1
#define vDiv 1
#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		// calculate height of the sprite on screen
		int spriteHeight = (int)fabs((HEIGHT / transformY) / vDiv); // using "transformY" instead of the real distance prevents fisheye
		// calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
		if (drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;

		// calculate width of the sprite
		int spriteWidth = (int)fabs((HEIGHT / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;

		// loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_WIDTH / spriteWidth) / 256);
			// the conditions in the if are:
			// 1) it's in front of camera plane so you don't see things behind you
			// 2) it's on the screen (left)
			// 3) it's on the screen (right)
			// 4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < data->zbuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) // for every pixel of the current stripe
				{
					int d = (y - vMoveScreen) * 256 - HEIGHT * 128 + spriteHeight * 128; // 256 and 128 factors to avoid floats
					int texY = ((d * TEXTURE_HEIGHT) / spriteHeight) / 256;
					int color = ((int **)data->texture)[sprite[spriteOrder[i]].texture][TEXTURE_WIDTH * texY + texX]; // get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						data->buf[y][stripe] = color; // paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}