/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:02:58 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 17:19:23 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extract_line(t_user *user, size_t pos)
{
	size_t	start;
	size_t	end;

	start = 2;
	while (user->info[pos][start] == ' ')
		start++;
	end = ft_strlen(user->info[pos]) - 1;
	while (user->info[pos][end] == ' ')
		end--;
	user->info[pos][end + 1] = '\0';
	if (user->info[pos][0] == 'N')
		user->no_path = &user->info[pos][start];
	if (user->info[pos][0] == 'S')
		user->so_path = &user->info[pos][start];
	if (user->info[pos][0] == 'W')
		user->we_path = &user->info[pos][start];
	if (user->info[pos][0] == 'E')
		user->ea_path = &user->info[pos][start];
}
