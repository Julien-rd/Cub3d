/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:47:08 by jromann           #+#    #+#             */
/*   Updated: 2026/01/12 18:56:36 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calulate_plane_vector(t_vector *dir, t_vector *plane, int flag)
{
	if (flag == LEFT)
	{
		plane->x = -(FOV_LEN * dir->x);
		plane->y = FOV_LEN * dir->y;
	}
	else
	{
		plane->y = -(FOV_LEN * dir->y);
		plane->x = FOV_LEN * dir->x;
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
            break;
    }
}

static char *get_texture(t_dda *ray, t_user *user)
{
	if(ray->side == 0)
	{
		if(ray->ray_dir_x >= 0)
			return user->ea_path;
		return user->we_path;
	}
	else
	{
		if(ray->ray_dir_y >= 0)
			return user->so_path;
		return user->no_path;
	}
}

typedef struct s_draw_utils {
	int start;
	int end;
	char *texture;
} t_draw_utils;

static void init_draw_data(t_draw_utils *draw_data, t_dda *ray, t_user *user)
{
	int line_height;
	
	line_height = (int)(SCREEN_WIDTH / ray->perp_wall_dist);;
	draw_data->start = line_height / 2 + SCREEN_WIDTH / 2;
	// printf("%d\n", draw_data->start);
	if (draw_data->start < 0)
		draw_data->start = 0;
	draw_data->end = line_height / 2 + SCREEN_WIDTH / 2;
	if (draw_data->end >= SCREEN_WIDTH)
		draw_data->end = SCREEN_WIDTH - 1;
	draw_data->texture = get_texture(ray, user);
}

static void draw_line(t_dda *ray, t_user *user, int screen_x)
{
	t_draw_utils draw_data;
	int y;
	
	y = 0;
	init_draw_data(&draw_data, ray, user);
    while (y < draw_data.start)
    {
        mlx_pixel_put(user->mlx, user->mlx_win, screen_x, y, 0x87CEEB);
        y++;
    }
    y = draw_data.start;
    while (y <= draw_data.end)
    {
        mlx_pixel_put(user->mlx, user->mlx_win, screen_x, y, 0x8B0000 );
        y++;
    }
    y = draw_data.end + 1;
    while (y < SCREEN_HEIGHT)
    {
        mlx_pixel_put(user->mlx, user->mlx_win, screen_x, y, 0x8B4513);
        y++;
    }
	
}

void	calculate_ray(t_user *user, int screen_x)
{
	t_dda ray;
	init_dda(&ray, user, screen_x);
	get_wall(&ray, user);
	calculate_per_wall_dist(&ray);
	draw_line(&ray, user, screen_x);
}

void draw_ray(t_user *user)
{
	// int col;
	int row;
	
	row = 0;
	while(row < SCREEN_WIDTH)
	{
		calculate_ray(user, row);
		// while(col < SCREEN_HEIGHT)
		// {
		// 	calculate_ray(user, col);
		// 	col++;
		// }
		row++;
	}
}