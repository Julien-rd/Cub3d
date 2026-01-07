/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:11:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/07 11:36:36 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_input(char *file_name, t_user *user)
{
	char	*input;

	input = read_file_to_string(file_name);
	if(!input)
		cleanup(user, ERROR, "Error\nEmpty file !\n");
	create_and_validate_map(input, user);
	parse_info(user);
	return (0);
}
