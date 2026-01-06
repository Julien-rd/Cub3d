/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:18:23 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 15:59:39 by jromann          ###   ########.fr       */
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

int		parse_map(char *input, t_user *user);
char	*read_file_to_string(char *file_name);

#endif
