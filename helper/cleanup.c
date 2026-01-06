/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:14:03 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 18:13:21 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free2d(char **str)
{
	size_t	iter;

	iter = 0;
	if (!str)
		return ;
	while (str[iter])
	{
		free(str[iter]);
		iter++;
	}
	free(str);
}

void	cleanup(t_user *user, int flag, char *msg)
{
	free2d(user->info);
	free2d(user->map);
	if (flag == PERROR || flag == ERROR)
	{
		if (msg != NULL && flag == PERROR)
			perror(msg);
		if (msg != NULL && flag == ERROR)
			write(2, msg, ft_strlen(msg));
		exit(1);
	}
	exit(0);
}
