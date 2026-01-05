/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:11:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/05 16:03:28 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free2d(char **str)
{
	size_t	iter;

	iter = 0;
	if (!str)
		return ;
	while (str[iter])
	{
		free(str[iter]);
		iter++;
	}
	free(str);
}

int	valid_char(char c)
{
	if (c != '1' && c != ' ') //&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	else
		return (0);
}

int	should_be_a_wall(t_user *user, size_t x, size_t y)
{
	size_t	line_len_above;
	size_t	line_len_below;

	if (x == 0 || y == 0)
		return (valid_char(user->map[y][x]));
	if (user->map[y + 1] == NULL || user->map[y][x + 1] == '\0')
		return (valid_char(user->map[y][x]));
	line_len_above = ft_strlen(user->map[y - 1]);
	line_len_below = ft_strlen(user->map[y + 1]);
	if (line_len_above <= x + 1 || line_len_below <= x + 1)
		return (valid_char(user->map[y][x]));
	if (user->map[y - 1][x] == ' ' || user->map[y + 1][x] == ' ')
		return (valid_char(user->map[y][x]));
	if (user->map[y - 1][x + 1] == ' ' || user->map[y + 1][x + 1] == ' ')
		return (valid_char(user->map[y][x]));
	if (user->map[y - 1][x - 1] == ' ' || user->map[y + 1][x - 1] == ' ')
		return (valid_char(user->map[y][x]));
	if (user->map[y][x - 1] == ' ' || user->map[y][x + 1] == ' ')
		return (valid_char(user->map[y][x]));
	return (0);
}

int	valid_line(t_user *user, size_t pos)
{
	size_t	iter;

	iter = 0;
	while (user->map[pos][iter])
	{
		if (user->map[pos][iter] != ' ' && user->map[pos][iter] != '1'
			&& user->map[pos][iter] != '0')
		{
			if ((user->map[pos][iter] == 'N' || user->map[pos][iter] == 'S'
					|| user->map[pos][iter] == 'E'
					|| user->map[pos][iter] == 'W') && user->start_dir == 'D')
				user->start_dir = user->map[pos][iter];
			else
				return (1);
		}
		if (should_be_a_wall(user, iter, pos) == 1)
			return (1);
		iter++;
	}
	return (0);
}

void	check_format(char *name)
{
	size_t	iter;

	iter = 0;
	while (name[iter])
		iter++;
	if (iter < 5)
	{
		write(2, "Error\nWrong format !\n", 21);
		exit(1);
	}
	if (ft_strncmp(".cub", &name[iter - 4], 4) != 0)
	{
		write(2, "Error\nWrong format !\n", 21);
		exit(1);
	}
}

void	initialise_data(char *input, t_user *user)
{
	user->start_dir = 'D';
	user->map = ft_split(input, '\n');
	if (user->map == NULL)
	{
		perror("initialise_data");
		exit(1);
	}
}

void	valid_input(t_user *user)
{
	size_t	iter;

	iter = 0;
	while (user->map[iter])
	{
		if (valid_line(user, iter) == 1)
		{
			write(2, "Error\nInvalid input !\n", 22);
			free2d(user->map);
			exit(1);
		}
		iter++;
	}
}

int	parse_map(char *input, t_user *user)
{
    // int fd;
	check_format(input);
    // fd = open(input, RDONLY);
	initialise_data(input, user);
	valid_input(user);
	return (0);
}