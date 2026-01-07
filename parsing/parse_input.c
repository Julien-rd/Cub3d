/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:11:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/07 15:19:06 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	final_check(t_user *user)
{
	if (user->we_path == NULL || user->so_path == NULL || user->ea_path == NULL
		|| user->no_path == NULL)
		cleanup(user, ERROR, "Error\nNo path found !\n");
	if (user->start_dir == 'D')
		cleanup(user, ERROR, "Error\nNo direction found !\n");
	if (user->floor.red == -1 || user->floor.blue == -1 || user->floor.green ==
		-1)
		cleanup(user, ERROR, "Error\nNo color found !\n");
	if (user->ceiling.red == -1 || user->ceiling.blue == -1
		|| user->ceiling.green == -1)
		cleanup(user, ERROR, "Error\nNo color found !\n");
	if (!user->info || !user->map)
		cleanup(user, ERROR, "Error\nInvalid input !\n");
}

int	parse_input(char *file_name, t_user *user)
{
	char	*input = NULL;

	input = read_file_to_string(file_name);
	if (!input)
		cleanup(user, ERROR, "Error\nEmpty file !\n");
	create_and_validate_map(input, user);
	parse_info(user);
	final_check(user);
	return (0);
}
