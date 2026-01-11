/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:19:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/09 17:53:16 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_dda
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		pos_x;
	double		pos_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_wall_dist;
}				t_dda;

typedef struct s_user
{
	char		start_dir;
	t_vector	player_pos;
	t_vector	dir_vec;
	t_vector	plane_vec;
	char		**map;
	char		**info;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_rgb		floor;
	t_rgb		ceiling;
	void		*mlx;
	void		*mlx_win;
}				t_user;

#endif