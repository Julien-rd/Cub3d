/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:58:33 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 14:28:29 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_wall_at(t_user *user, double x, double y)
{
	int	map_x;
	int	map_y;
	int	map_height;

	map_x = (int)x;
	map_y = (int)y;
	map_height = 0;
	while (user->map[map_height])
		map_height++;
	if (map_y < 0 || map_y >= map_height)
		return (true);
	if (map_x < 0 || map_x >= (int)ft_strlen(user->map[map_y]))
		return (true);
	return (user->map[map_y][map_x] == '1');
}

static bool	check_collision(t_user *user, double x, double y)
{
	double	buffer;

	buffer = 0.2;
	if (is_wall_at(user, x - buffer, y - buffer))
		return (true);
	if (is_wall_at(user, x + buffer, y - buffer))
		return (true);
	if (is_wall_at(user, x - buffer, y + buffer))
		return (true);
	if (is_wall_at(user, x + buffer, y + buffer))
		return (true);
	return (false);
}

void	move_forward(t_user *user)
{
	double	new_x;
	double	new_y;

	new_x = user->player_pos.x + user->dir_vec.x * MOVE_S;
	new_y = user->player_pos.y + user->dir_vec.y * MOVE_S;
	if (!check_collision(user, new_x, new_y))
	{
		user->player_pos.x = new_x;
		user->player_pos.y = new_y;
	}
}

void	move_backward(t_user *user)
{
	double	new_x;
	double	new_y;

	new_x = user->player_pos.x - user->dir_vec.x * MOVE_S;
	new_y = user->player_pos.y - user->dir_vec.y * MOVE_S;
	if (!check_collision(user, new_x, new_y))
	{
		user->player_pos.x = new_x;
		user->player_pos.y = new_y;
	}
}

void	move_left(t_user *user)
{
	double	new_x;
	double	new_y;

	new_x = user->player_pos.x - user->plane_vec.x * MOVE_S;
	new_y = user->player_pos.y - user->plane_vec.y * MOVE_S;
	if (!check_collision(user, new_x, new_y))
	{
		user->player_pos.x = new_x;
		user->player_pos.y = new_y;
	}
}

void	move_right(t_user *user)
{
	double	new_x;
	double	new_y;

	new_x = user->player_pos.x + user->plane_vec.x * MOVE_S;
	new_y = user->player_pos.y + user->plane_vec.y * MOVE_S;
	if (!check_collision(user, new_x, new_y))
	{
		user->player_pos.x = new_x;
		user->player_pos.y = new_y;
	}
}
