/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:58:33 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 14:08:33 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_user *user)
{
	double	new_x;
	double	new_y;

	new_x = user->player_pos.x + user->dir_vec.x * MOVE_S;
	new_y = user->player_pos.y + user->dir_vec.y * MOVE_S;
	if (user->map[(int)new_y][(int)new_x] != '1')
	{
		user->player_pos.x = new_x;
		user->player_pos.y = new_y;
	}
}

void	move_backward(t_user *user)
{
	double	new_x;
	double	new_y;

	new_x = user->player_pos.x + user->dir_vec.x * MOVE_S;
	new_y = user->player_pos.y + user->dir_vec.y * MOVE_S;
	if (user->map[(int)new_y][(int)new_x] != '1')
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
	if (user->map[(int)new_y][(int)new_x] != '1')
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
	if (user->map[(int)new_y][(int)new_x] != '1')
	{
		user->player_pos.x = new_x;
		user->player_pos.y = new_y;
	}
}
