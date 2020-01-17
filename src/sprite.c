/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:38:59 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/17 15:46:01 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_sprite	*new_sprite(int x, int y)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
		return (NULL);
	new->x = (double)x + 0.5;
	new->y = (double)y + 0.5;
	new->dist = 0;
	new->next = NULL;
	return (new);
}

void		sprite_add_back(t_sprite *spr, int x, int y)
{
	t_sprite	*sp;

	sp = spr;
	while (sp->next)
		sp = sp->next;
	sp->next = new_sprite(x, y);
}

void		clear_sprite(t_sprite *begin)
{
	t_sprite	*sp;
	t_sprite	*next;

	sp = begin;
	while (sp)
	{
		next = sp->next;
		free(sp);
		sp = next;
	}
	begin = NULL;
}

int			is_sprite_save(t_sprite *spr, int x, int y)
{
	while (spr)
	{
		if (spr->x <= (double)x + 0.51 &&
			spr->x >= (double)x + 0.49 &&
			spr->y <= (double)y + 0.51
			&& spr->y >= (double)y + 0.49)
			return (1);
		spr = spr->next;
	}
	return (0);
}

void		save_data_spr(t_sprite *sprite, int x, int y)
{
	if (is_sprite_save(sprite, x, y) == 1)
		return ;
	sprite_add_back(sprite, x, y);
}
