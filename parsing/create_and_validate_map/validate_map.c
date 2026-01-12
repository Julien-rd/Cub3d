/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:41:57 by jromann           #+#    #+#             */
/*   Updated: 2026/01/12 20:16:37 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_char(char c)
{
	if (c != '1' && c != ' ')
		return (1);
	else
		return (0);
}

static int	should_be_a_wall(t_user *user, size_t x, size_t y)
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

static void player_start_pos(t_user *user, size_t pos, size_t iter)
{
	user->start_dir = user->map[pos][iter];
	if (user->start_dir == 'N')
	{
		user->dir_vec.x = 0;
		user->dir_vec.y = -1;
	}
	if (user->start_dir == 'S')
	{
		user->dir_vec.x = 0;
		user->dir_vec.y = 1;
	}
	if (user->start_dir == 'W')
	{
		user->dir_vec.x = -1;
		user->dir_vec.y = 0;
	}
	if (user->start_dir == 'E')
	{
		user->dir_vec.x = 1;
		user->dir_vec.y = 0;
	}
	user->player_pos.x = (double)iter + 0.5;
	user->player_pos.y = (double)pos + 0.5;
	calulate_plane_vector(&user->player_pos, &user->plane_vec, RIGHT);
}

static int	valid_line(t_user *user, size_t pos)
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
				player_start_pos(user, pos, iter);
			else
				return (1);
		}
		if (should_be_a_wall(user, iter, pos) == 1)
			return (1);
		iter++;
	}
	return (0);
}

void	valid_map(t_user *user)
{
	size_t	iter;

	iter = 0;
	while (user->map[iter])
	{
		if (valid_line(user, iter) == 1)
			cleanup(user, ERROR, "Error\nInvalid input !\n");
		iter++;
	}
}
