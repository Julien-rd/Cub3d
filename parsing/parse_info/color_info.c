/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:01:41 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 18:12:50 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialise_colors(char colors[3][4])
{
	size_t	iter;

	iter = 0;
	while (iter < 3)
	{
		colors[iter][0] = '2';
		colors[iter][1] = '5';
		colors[iter][2] = '6';
		colors[iter][3] = '\0';
		iter++;
	}
}

static void	extract_colors(t_user *user, char *line, char colors[3][4])
{
	size_t	iter;
	size_t	digit;
	size_t	color_digit;

	iter = skip_spaces(line);
	digit = 0;
	color_digit = 0;
	while (line[iter])
	{
		if (line[iter] == ',')
		{
			iter++;
			digit++;
			color_digit = 0;
			if (digit > 3)
				cleanup(user, ERROR, "Error\nInvalid input !\n");
		}
		iter += skip_spaces(&line[iter]);
		if (!ft_isdigit(line[iter]) || color_digit == 3)
			cleanup(user, ERROR, "Error\nInvalid input !\n");
		colors[digit][color_digit] = line[iter];
		colors[digit][color_digit + 1] = '\0';
		iter++;
	}
}

void	color_info(t_user *user, char flag, size_t pos)
{
	char	colors[3][4];

	initialise_colors(colors);
	extract_colors(user, &user->info[pos][1], colors);
	if (flag == 'F')
	{
		user->floor.red = ft_atoi(colors[0]);
		user->floor.blue = ft_atoi(colors[1]);
		user->floor.green = ft_atoi(colors[2]);
		if (user->floor.red > 255 || user->floor.blue > 255
			|| user->floor.green > 255)
			cleanup(user, ERROR, "Error\nInvalid input !\n");
	}
	if (flag == 'C')
	{
		user->ceiling.red = ft_atoi(colors[0]);
		user->ceiling.blue = ft_atoi(colors[1]);
		user->ceiling.green = ft_atoi(colors[2]);
		if (user->ceiling.red > 255 || user->ceiling.blue > 255
			|| user->ceiling.green > 255)
			cleanup(user, ERROR, "Error\nInvalid input !\n");
	}
}
