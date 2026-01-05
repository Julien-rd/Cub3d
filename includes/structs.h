/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:19:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/05 15:20:35 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_user
{
	char	start_dir;
	size_t	pos_x;
	size_t	pos_y;
	char	**map;
}			t_user;

#endif