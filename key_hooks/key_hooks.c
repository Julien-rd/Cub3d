/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:43 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 14:25:25 by jromann          ###   ########.fr       */
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
	int	moved;

	moved = 0;
	if (keycode == 65307)
		cleanup(user, SUCCESS, NULL);
	if (keycode == 119)
	{
		move_forward(user);
		moved = 1;
	}
	if (keycode == 115)
	{
		move_backward(user);
		moved = 1;
	}
	if (keycode == 97)
	{
		move_left(user);
		moved = 1;
	}
	if (keycode == 100)
	{
		move_right(user);
		moved = 1;
	}
	if (keycode == 65361)
	{
		rotate_left(user);
		moved = 1;
	}
	if (keycode == 65363)
	{
		rotate_right(user);
		moved = 1;
	}
	if (moved)
	{
		draw_ray(user);
		mlx_put_image_to_window(user->mlx, user->mlx_win, user->img, 0, 0);
	}
	return (0);
}

void	set_up_hooks(t_user *user)
{
	mlx_hook(user->mlx_win, 2, 1L << 0, key_hook, user);
	mlx_hook(user->mlx_win, 17, 1L << 17, close_hook, user);
}