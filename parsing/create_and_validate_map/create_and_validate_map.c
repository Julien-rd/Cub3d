/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_validate_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:56:37 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:07 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_and_validate_map(char *input, t_user *user)
{
	size_t	iter;

	iter = map_exists(input, user);
	check_empty_lines(&input[iter], user);
	user->info = ft_split(input, '\n');
	user->map = ft_split(&input[iter], '\n');
	if (user->map == NULL || user->info == NULL)
		cleanup(user, PERROR, "create_and_validate_map");
	valid_map(user);
}
