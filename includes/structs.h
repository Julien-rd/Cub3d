/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:19:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/14 11:48:16 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_image
{
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_image;

typedef struct s_texture
{
	void			*img;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_texture;

typedef struct s_dda
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			pos_x;
	double			pos_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
}					t_dda;

typedef struct s_user
{
	char			start_dir;
	t_vector		player_pos;
	t_vector		dir_vec;
	t_vector		plane_vec;
	char			**map;
	char			**info;
	void			*no_path;
	void			*so_path;
	void			*we_path;
	void			*ea_path;
	t_rgb			floor;
	t_rgb			ceiling;
	unsigned int	ceiling_c;
	unsigned int	floor_c;
	void			*mlx;
	void			*mlx_win;
	t_texture		n_tex;
	t_texture		s_tex;
	t_texture		w_tex;
	t_texture		e_tex;
	void			*img;
	t_image			image;
}					t_user;

#endif