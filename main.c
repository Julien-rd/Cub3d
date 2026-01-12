/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:21:15 by jromann           #+#    #+#             */
/*   Updated: 2026/01/12 21:09:20 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	intialise_data(t_user *user)
{
	user->start_dir = 'D';
	user->plane_vec.x = 0;
	user->plane_vec.y = 0;
	user->player_pos.x = 0;
	user->player_pos.y = 0;
	user->dir_vec.x = 0;
	user->dir_vec.y = 0;
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
	user->img = mlx_new_image(user->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	user->image.img_data = mlx_get_data_addr(user->img, &user->image.bpp,
			&user->image.size_line, &user->image.endian);
}

static void load_texture(t_user *user)
{
	user->n_tex.img = mlx_xpm_file_to_image(user->mlx, user->no_path, &user->n_tex.width, &user->n_tex.height);
	user->n_tex.data = mlx_get_data_addr(user->n_tex.img, &user->n_tex.bpp, &user->n_tex.line_len, &user->n_tex.endian);

	user->s_tex.img = mlx_xpm_file_to_image(user->mlx, user->so_path, &user->s_tex.width, &user->s_tex.height);
	user->s_tex.data = mlx_get_data_addr(user->s_tex.img, &user->s_tex.bpp, &user->s_tex.line_len, &user->s_tex.endian);
	
	user->w_tex.img = mlx_xpm_file_to_image(user->mlx, user->we_path, &user->w_tex.width, &user->w_tex.height);
	user->w_tex.data = mlx_get_data_addr(user->w_tex.img, &user->w_tex.bpp, &user->w_tex.line_len, &user->w_tex.endian);
	
	user->e_tex.img = mlx_xpm_file_to_image(user->mlx, user->ea_path, &user->e_tex.width, &user->e_tex.height);
	user->e_tex.data = mlx_get_data_addr(user->e_tex.img, &user->e_tex.bpp, &user->e_tex.line_len, &user->e_tex.endian);
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
	load_texture(&user);
	open_window(&user);
	draw_ray(&user);
	mlx_put_image_to_window(user.mlx, user.mlx_win, user.img, 0, 0);
	set_up_hooks(&user);
	cleanup(&user, SUCCESS, NULL);
	return (0);
}
