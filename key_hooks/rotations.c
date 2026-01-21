/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:13:14 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 14:23:02 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_user *user)
{
	double	dir_x;
	double	plane_x;
	double	len;

	dir_x = user->dir_vec.x;
	plane_x = user->plane_vec.x;
	user->dir_vec.x = user->dir_vec.x * cos(ROT_S) - user->dir_vec.y
		* sin(ROT_S);
	user->dir_vec.y = dir_x * sin(ROT_S) + user->dir_vec.y * cos(ROT_S);
	user->plane_vec.x = user->plane_vec.x * cos(ROT_S) - user->plane_vec.y
		* sin(ROT_S);
	user->plane_vec.y = plane_x * sin(ROT_S) + user->plane_vec.y * cos(ROT_S);
	len = sqrt(user->dir_vec.x * user->dir_vec.x + user->dir_vec.y
			* user->dir_vec.y);
	user->dir_vec.x /= len;
	user->dir_vec.y /= len;
}

void	rotate_right(t_user *user)
{
	double dir_x;
	double plane_x;
	double len;

	dir_x = user->dir_vec.x;
	plane_x = user->plane_vec.x;
	user->dir_vec.x = user->dir_vec.x * cos(-ROT_S) - user->dir_vec.y
		* sin(-ROT_S);
	user->dir_vec.y = dir_x * sin(-ROT_S) + user->dir_vec.y * cos(-ROT_S);
	user->plane_vec.x = user->plane_vec.x * cos(-ROT_S) - user->plane_vec.y
		* sin(-ROT_S);
	user->plane_vec.y = plane_x * sin(-ROT_S) + user->plane_vec.y * cos(-ROT_S);
	len = sqrt(user->dir_vec.x * user->dir_vec.x + user->dir_vec.y
			* user->dir_vec.y);
	user->dir_vec.x /= len;
	user->dir_vec.y /= len;
}