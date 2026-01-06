/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:19:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 11:39:28 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rgb
{
	int red;
	int green;
	int blue;
}			t_rgb;

typedef struct s_user
{
	char	start_dir;
	size_t	pos_x;
	size_t	pos_y;
	char	**map;
	char	**info;
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	t_rgb floor;
	t_rgb ceiling;
}			t_user;

#endif