/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:47:08 by jromann           #+#    #+#             */
/*   Updated: 2026/01/14 12:23:04 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calulate_plane_vector(t_vector *dir, t_vector *plane, int flag)
{
	if (flag == LEFT)
	{
		plane->x = -(FOV_LEN * dir->y);
		plane->y = FOV_LEN * dir->x;
	}
	else
	{
		plane->x = FOV_LEN * dir->y;
		plane->y = -(FOV_LEN * dir->x);
	}
}

static void	init_dda_edge_cases(t_dda *ray)
{
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
}

static void	init_dda(t_dda *ray, t_user *user, int screen_x)
{
	ray->camera_x = 2 * screen_x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = user->dir_vec.x + user->plane_vec.x * ray->camera_x;
	ray->ray_dir_y = user->dir_vec.y + user->plane_vec.y * ray->camera_x;
	ray->pos_x = user->player_pos.x;
	ray->pos_y = user->player_pos.y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->delta_dist_x = 1e30;
	ray->delta_dist_y = 1e30;
	ray->side = 0;
	ray->step_x = 1;
	ray->step_y = 1;
	ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	init_dda_edge_cases(ray);
}

static void	calculate_per_wall_dist(t_dda *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
}

static void	get_wall(t_dda *ray, t_user *user)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (user->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

static t_texture	*get_texture(t_dda *ray, t_user *user)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x >= 0)
			return (&user->e_tex);
		return (&user->w_tex);
	}
	else
	{
		if (ray->ray_dir_y >= 0)
			return (&user->s_tex);
		return (&user->n_tex);
	}
}

typedef struct s_draw_utils
{
	int				start;
	int				end;
	t_texture		*texture;
	double			wall_x;
	int				tex_x;
}					t_draw_utils;

static void	init_draw_data(t_draw_utils *draw_data, t_dda *ray, t_user *user)
{
	int	line_height;

	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw_data->start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_data->start < 0)
		draw_data->start = 0;
	draw_data->end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_data->end >= SCREEN_HEIGHT)
		draw_data->end = SCREEN_HEIGHT - 1;
	draw_data->texture = get_texture(ray, user);
	if (ray->side == 0)
		draw_data->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		draw_data->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	draw_data->wall_x -= floor(draw_data->wall_x);
	draw_data->tex_x = (int)(draw_data->wall_x
			* (double)draw_data->texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		draw_data->tex_x = draw_data->texture->width - draw_data->tex_x - 1;
}

void	ft_put_pixel(t_image image, int x, int y, int color)
{
	int	offset;

	offset = (y * image.size_line) + (x * (image.bpp / 8));
	*(int *)(image.img_data + offset) = color;
}

static void	draw_line(t_dda *ray, t_user *user, int screen_x)
{
	t_draw_utils	draw_data;
	int				y;
	int				tex_y;
	int				color;
	double			step;
	double			tex_pos;

	init_draw_data(&draw_data, ray, user);
	y = 0;
	while (y < draw_data.start)
	{
		ft_put_pixel(user->image, screen_x, y, user->ceiling_c);
		y++;
	}
	step = (double)draw_data.texture->height / (draw_data.end
			- draw_data.start);
	tex_pos = 0;
	y = draw_data.start;
	while (y <= draw_data.end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= draw_data.texture->height)
			tex_y = draw_data.texture->height - 1;
		tex_pos += step;
		color = *(int *)(draw_data.texture->data + (tex_y
					* draw_data.texture->line_len + draw_data.tex_x
					* (draw_data.texture->bpp / 8)));
		ft_put_pixel(user->image, screen_x, y, color);
		y++;
	}
	y = draw_data.end + 1;
	while (y < SCREEN_HEIGHT)
	{
		ft_put_pixel(user->image, screen_x, y, user->floor_c);
		y++;
	}
}

void	calculate_ray(t_user *user, int screen_x)
{
	t_dda	ray;

	init_dda(&ray, user, screen_x);
	get_wall(&ray, user);
	calculate_per_wall_dist(&ray);
	draw_line(&ray, user, screen_x);
}

void	draw_ray(t_user *user)
{
	int row;

	row = 0;
	while (row < SCREEN_WIDTH)
	{
		calculate_ray(user, row);
		row++;
	}
}