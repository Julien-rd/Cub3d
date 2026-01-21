/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:13:14 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 14:16:32 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_user *user)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = user->dir_vec.x;
	old_plane_x = user->plane_vec.x;
	user->dir_vec.x = user->dir_vec.x * cos(ROT_S) - user->dir_vec.y
		* sin(ROT_S);
	user->dir_vec.y = old_dir_x * sin(ROT_S) + user->dir_vec.y * cos(ROT_S);
	user->plane_vec.x = user->plane_vec.x * cos(ROT_S) - user->plane_vec.y
		* sin(ROT_S);
	user->plane_vec.y = old_plane_x * sin(ROT_S) + user->plane_vec.y
		* cos(ROT_S);
}

void	rotate_right(t_user *user)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = user->dir_vec.x;
	old_plane_x = user->plane_vec.x;
	user->dir_vec.x = user->dir_vec.x * cos(-ROT_S) - user->dir_vec.y
		* sin(-ROT_S);
	user->dir_vec.y = old_dir_x * sin(-ROT_S) + user->dir_vec.y * cos(-ROT_S);
	user->plane_vec.x = user->plane_vec.x * cos(-ROT_S) - user->plane_vec.y
		* sin(-ROT_S);
	user->plane_vec.y = old_plane_x * sin(-ROT_S) + user->plane_vec.y
		* cos(-ROT_S);
}