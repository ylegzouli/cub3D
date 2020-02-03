/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:56:14 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/01/19 19:04:44 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		main(int ac, char **av)
{
	t_parse		*data;
	t_mlx		*mlx;

	data = NULL;
	mlx = NULL;
	if (!(check_arg(ac, av)))
	{
		write(1, "Erreur Arguments\n", 17);
		return (0);
	}
	if (!(start(mlx, data, ac, av)))
	{
		free(data);
		free(mlx);
		write(1, "Erreur initialisation\n", 22);
		return (0);
	}
	return (1);
}

int		start(t_mlx *mlx, t_parse *data, int ac, char **av)
{
	t_map		*map;
	t_player	*player;
	t_hook		*hook;
	t_raycast	*ray;

	if (!(init_data(&map, &player, &mlx, &hook)))
		return (0);
	if (!(init_data2(&data, &ray, &hook)))
		return (0);
	if (!(parse_file(av, &data, &map, &player)))
		return (0);
	if (!(check_map(map)) || !(check_size_map(map->map, map)))
		return (0);
	get_texture_fnc(ray, data);
	if (!(init_mlx(mlx, data)))
		return (0);
	if (!(init_texture(data, mlx)))
		return (0);
	affichage(mlx, ray, map, player);
	opt_save_bmp(mlx, hook, ac, av);
	mlx_hook(mlx->win, 2, 1L << 0, hook_keydown, hook);
	mlx_hook(mlx->win, 17, 0, exit_all, hook);
	mlx_loop(mlx->ptr);
	return (1);
}

void	exit_error(t_hook *hook)
{
	write(1, "Erreur\n", 7);
	exit_all(hook);
}

int		check_arg(int ac, char **av)
{
	int i;

	if (ac == 2 || ac == 3)
	{
		i = ft_strlen(av[1]) - 1;
		if (i <= 4)
			return (0);
		if (av[1][i] != 'b' || av[1][i - 1] != 'u' || av[1][i - 2] != 'c'
			|| av[1][i - 3] != '.')
			return (0);
		if (ac == 3 && ft_strncmp("-save", av[2], 5) != 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

void	exit_key(t_map *map, t_parse *data)
{
	write(1, "Erreur initialisation\n", 22);
	free(map);
	free(data);
	exit(1);
}
