/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:51 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/12/16 20:06:35 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		put_pixel(t_image *img, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= LARGEUR_SCREEN || y >= HAUTEUR_SCREEN))
	{
		*(int *)(img->data + ((x + y * LARGEUR_SCREEN)  * img->bpp)) = 16711680;
	}
}

t_image		*new_image(t_mlx *mlx, int l, int h)
{
	t_image		*img;
	
	if (!(img = malloc(sizeof(t_image))))
		return (NULL);
	img->img = mlx_new_image(mlx->ptr, l, h);
	img->data = mlx_get_data_addr(img->img, &(img->bpp), &(img->size), &(img->en));
	img->bpp = img->bpp / 8;
	return (img);
}
/*
t_image		*new_xpm_image(t_mlx *mlx, char *xpm, int l, int h)
{
	t_image 	*img;

	if (!(img = malloc(sizeof(t_image))))
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx->ptr, xpm, l, h);
	img->data = mlx_get_data_addr(img->img, &(img->bpp), &(img->size), &(img->en));
	img->bpp = img->bpp / 8;
	return (img);
}
*/
void		clear_image(t_image *img, int l, int h)
{
	int		size;

	size = l * h * img->bpp;
	ft_bzero(img->data, size);
}
