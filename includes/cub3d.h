/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:18:23 by jromann           #+#    #+#             */
/*   Updated: 2026/01/07 11:44:05 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FLOOR 0
# define CEILING 1
# define NO 2
# define SO 3
# define WE 4
# define EA 5

# define SUCCESS 0
# define ERROR 1
# define PERROR 2

//*************** PARSING **************//

// create_and_validate_map
void	create_and_validate_map(char *input, t_user *user);
size_t	map_exists(char *input, t_user *user);
void	check_empty_lines(char *map, char *input, t_user *user);
void	valid_map(t_user *user);

// parse_info
void	color_info(t_user *user, char flag, size_t pos);
void	parse_info(t_user *user);
void	extract_line(t_user *user, size_t pos);

int		parse_input(char *file_name, t_user *user);
char	*read_file_to_string(char *file_name);

//*************** HELPER **************//
void	cleanup(t_user *user, int flag, char *msg);
void	free2d(char **str);
size_t	skip_spaces(char *str);

#endif
