/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:01:41 by jromann           #+#    #+#             */
/*   Updated: 2026/01/21 13:51:53 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_2dlen(t_user *user, char **colors)
{
	size_t	iter;

	iter = 0;
	while (colors[iter])
		iter++;
	if (iter != 3)
		return (free2d(colors), cleanup(user, ERROR,
				"Error\nInvalid input !\n"));
}

static char	**prepare_color_info(t_user *user, size_t pos)
{
	char	**colors;
	char	**trim_colors;
	size_t	iter;

	iter = 0;
	colors = ft_split(&user->info[pos][1], ',');
	if (!colors)
		cleanup(user, PERROR, "color_info");
	check_2dlen(user, colors);
	trim_colors = (char **)ft_calloc(sizeof(char *), 4);
	if (!trim_colors)
		return (free2d(colors), cleanup(user, PERROR, "color_info"), NULL);
	while (colors[iter])
	{
		trim_colors[iter] = ft_strtrim(colors[iter], " ");
		if (!trim_colors[iter])
			return (free2d(trim_colors), free2d(colors), cleanup(user, PERROR,
					"color_info"), NULL);
		iter++;
	}
	return (free2d(colors), trim_colors);
}

static void	validate_colors(t_user *user, char **colors)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (colors[row])
	{
		if (ft_strlen(colors[row]) > 3)
			return (free2d(colors), cleanup(user, ERROR,
					"Error\nInvalid input !\n"));
		col = 0;
		while (colors[row][col])
		{
			if (!ft_isdigit(colors[row][col]))
				return (free2d(colors), cleanup(user, ERROR,
						"Error\nInvalid input !\n"));
			col++;
		}
		row++;
	}
}

static void	convert_colors(t_user *user, char **colors, char flag)
{
	if (flag == 'F')
	{
		user->floor.red = ft_atoi(colors[0]);
		user->floor.green = ft_atoi(colors[1]);
		user->floor.blue = ft_atoi(colors[2]);
		if (user->floor.red == -1 || user->floor.blue == -1
			|| user->floor.green == -1)
			return (free2d(colors), cleanup(user, ERROR,
					"Error\nInvalid input !\n"));
	}
	if (flag == 'C')
	{
		user->ceiling.red = ft_atoi(colors[0]);
		user->ceiling.green = ft_atoi(colors[1]);
		user->ceiling.blue = ft_atoi(colors[2]);
		if (user->ceiling.red == -1 || user->ceiling.blue == -1
			|| user->ceiling.green == -1)
			return (free2d(colors), cleanup(user, ERROR,
					"Error\nInvalid input !\n"));
	}
}

void	color_info(t_user *user, char flag, size_t pos)
{
	char **colors;

	colors = prepare_color_info(user, pos);
	validate_colors(user, colors);
	convert_colors(user, colors, flag);
	free2d(colors);
}