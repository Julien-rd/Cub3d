/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:43 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 14:12:27 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_hook(t_user *user)
{
	cleanup(user, SUCCESS, NULL);
	return (0);
}

static int	key_hook(int keycode, t_user *user)
{
	if (keycode == 65307)
		cleanup(user, SUCCESS, NULL);
	if (keycode == 119) // W
		move_forward(user);
	if (keycode == 115) // S
		move_backward(user);
	if (keycode == 97) // A
		move_left(user);
	if (keycode == 100) // D
		move_right(user);
	if (keycode == 65361) // Left Arrow
		rotate_left(user);
	if (keycode == 65363) // Right Arrow
		rotate_right(user);
	draw_ray(user);
	mlx_put_image_to_window(user->mlx, user->mlx_win, user->img, 0, 0);
	return (0);
}

void	set_up_hooks(t_user *user)
{
	mlx_hook(user->mlx_win, 2, 1L << 0, key_hook, user);
	mlx_hook(user->mlx_win, 17, 1L << 17, close_hook, user);
}