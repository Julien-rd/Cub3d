/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:21:15 by jromann           #+#    #+#             */
/*   Updated: 2026/01/07 11:31:29 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	intialise_data(t_user *user)
{
	user->start_dir = 'D';
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

int	main(int argc, char **argv)
{
	t_user	user;

	if (argc != 2)
		return (write(2, "Error\nExactly two arguments are required !\n", 43),
			1);
	intialise_data(&user);
	validate_file_extension(argv[1]);
	parse_input(argv[1], &user);
	printf("%s\n", user.we_path);
	cleanup(&user, SUCCESS, NULL);
	return (0);
}
