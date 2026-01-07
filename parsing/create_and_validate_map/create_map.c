/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:36:22 by jromann           #+#    #+#             */
/*   Updated: 2026/01/07 11:29:01 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_empty_line(char *line)
{
	size_t	iter;

	iter = 0;
	while (line[iter] == 32)
		iter++;
	if (line[iter] == '\n')
		return (true);
	return (false);
}

void	check_empty_lines(char *map, char *input, t_user *user)
{
	size_t	iter;
	bool	empty_line;

	empty_line = false;
	iter = 0;
	while (map[iter])
	{
		if (is_empty_line(&map[iter]))
			empty_line = true;
		else
		{
			if (empty_line == true)
				return (free(input), cleanup(user, ERROR,
						"Error\nEmpty line in map !\n"));
		}
		while (map[iter] != '\n' && map[iter])
			iter++;
		if (map[iter] != '\0')
			iter++;
	}
}

size_t	map_exists(char *input, t_user *user)
{
	size_t	iter;
	size_t	offset;

	iter = 0;
	while (input[iter])
	{
		if (input[iter] == '\n')
		{
			iter++;
			offset = 0;
			while (input[iter + offset] == 32)
				offset++;
			if (input[iter + offset] == '1')
				return (iter);
		}
		else
			iter++;
	}
	free(input);
	cleanup(user, ERROR, "Error\nNo map found !\n");
	return (0);
}
