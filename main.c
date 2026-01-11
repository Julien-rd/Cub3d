/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:21:15 by jromann           #+#    #+#             */
/*   Updated: 2026/01/09 18:06:04 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	intialise_data(t_user *user)
{
	user->start_dir = 'D';
	user->plane_vec.x = FOV_LEN; 
	user->info = NULL;
	user->map = NULL;
	user->we_path = NULL;
	user->so_path = NULL;
	user->ea_path = NULL;
	user->no_path = NULL;
	user->floor.red = -1;
	user->floor.blue = -1;
	user->floor.green = -1;
	user->ceiling.red = -1;
	user->ceiling.blue = -1;
	user->ceiling.green = -1;
}

static void	validate_file_extension(char *file_name)
{
	size_t	iter;

	iter = 0;
	while (file_name[iter])
		iter++;
	if (iter < 5)
	{
		write(2, "Error\nWrong format !\n", 21);
		exit(1);
	}
	if (ft_strncmp(".cub", &file_name[iter - 4], 4) != 0)
	{
		write(2, "Error\nWrong format !\n", 21);
		exit(1);
	}
}

static int	key_hook(int keycode, void *param)
{
	if (keycode == 65307)
		exit(0);
	(void)param;
	return (0);
}

void	set_up_hooks(t_user *user)
{
	mlx_hook(user->mlx_win, 2, 1L << 0, key_hook, NULL);
	// mlx_hook(user->mlx_win, 17, 1L << 17, ft_close_hook, NULL);
	mlx_loop(user->mlx);
}

static void	open_window(t_user *user)
{
	user->mlx = mlx_init();
	user->mlx_win = mlx_new_window(user->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
}

int	main(int argc, char **argv)
{
	t_user	user;

	if (argc != 2)
		return (write(2, "Error\nExactly two arguments are required !\n", 43),
			1);
	intialise_data(&user);
	validate_file_extension(argv[1]);
	parse_input(argv[1], &user);
	open_window(&user);
	draw_ray(&user);
	set_up_hooks(&user);
	cleanup(&user, SUCCESS, NULL);
	return (0);
}
