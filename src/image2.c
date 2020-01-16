/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:37:01 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/16 19:37:36 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void		destroy_image(t_image *img, t_mlx *mlx)
{
	if (img != NULL)
	{
		if (img->img != NULL)
			mlx_destroy_image(mlx->ptr, img->img);
		free(img);
	}
}
