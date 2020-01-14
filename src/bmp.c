/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:49:18 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/14 23:50:24 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void			opt_save_bmp(t_mlx *mlx, int ac, char **av)
{
	if (ac == 3)
	{
		if (ft_strncmp("-save", av[2], 5) == 0)
			save_bitmap("screen.bmp", mlx);
	}
}

void			int_to_char(char *str, int nb)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		str[i] = (unsigned char)(nb >> (i * 8));
		i++;
	}
}

void			save_bitmap(char *filename, t_mlx *mlx)
{
	int		i;
	int		fd;
	char	header[54];

	i = 0;
	while (i < 54)
	{
		header[i] = (unsigned char)0;
		i++;
	}
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, mlx->res_x * mlx->res_y * 4 + 54);
	int_to_char(header + 10, 54);
	int_to_char(header + 14, 40);
	int_to_char(header + 18, mlx->res_x);
	int_to_char(header + 22, mlx->res_y);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	fd = open(filename, O_RDWR | O_CREAT, 0666);
	write(fd, header, 54);
	bitmap_image(mlx, fd);
	close(fd);
}

void			bitmap_image(t_mlx *mlx, int fd)
{
	int				x;
	int				y;
	int				temp;
	unsigned char	color[3];
	int				*ptr;

	ptr = (int *)mlx->img->data;
	y = mlx->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < mlx->res_x)
		{
			temp = ptr[x + y * mlx->res_x];
			color[0] = temp % 256;
			temp /= 256;
			color[1] = temp % 256;
			temp /= 256;
			color[2] = temp % 256;
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}
