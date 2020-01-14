/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:37:51 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/14 23:58:58 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void		put_pixel(t_image *img, int x, int y, int color)
{
	*(int *)(img->data + ((x + y * LARGEUR_SCREEN) * img->bpp)) = color;
}

int			get_pixel(t_image *img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img->l || y >= img->h)
		return (0);
	return (*(int *)(img->data + ((x + y * img->l)
			* img->bpp)));
}

t_image		*new_image(t_mlx *mlx, int l, int h)
{
	t_image		*img;

	if (!(img = malloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img = mlx_new_image(mlx->ptr, l, h)))
		return (NULL);
	img->data = mlx_get_data_addr(img->img,
	&(img->bpp), &(img->size), &(img->en));
	img->bpp = img->bpp / 8;
	img->l = l;
	img->h = h;
	return (img);
}

t_image		*new_xpm_image(t_mlx *mlx, char *xpm)
{
	t_image		*img;

	if (!(img = malloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img = mlx_xpm_file_to_image(mlx->ptr,
		xpm, &(img->l), &(img->h))))
		return (NULL);
	img->data = mlx_get_data_addr(img->img, &(img->bpp),
	&(img->size), &(img->en));
	img->bpp = img->bpp / 8;
	img->l = img->size / img->bpp;
	img->h = img->size / img->bpp;
	return (img);
}

void		clear_image(t_image *img, int l, int h)
{
	int		size;

	size = l * h * img->bpp;
	ft_bzero(img->data, size);
}

void		destroy_image(t_image *img, t_mlx *mlx)
{
	if (img != NULL)
	{
		if (img->img != NULL)
			mlx_destroy_image(mlx->ptr, img->img);
		free(img);
	}
}
