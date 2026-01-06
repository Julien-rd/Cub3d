/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_to_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:49:34 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 16:09:26 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_realloc(char *in_str, size_t size)
{
	char	*ret_str;
	size_t	iter;

	iter = 0;
	ret_str = ft_calloc(size + 1, sizeof(char));
	if (!ret_str)
		return (free(in_str), NULL);
	if (in_str == NULL)
		return (ret_str);
	while (in_str[iter] && iter < size - 1)
	{
		ret_str[iter] = in_str[iter];
		iter++;
	}
	free(in_str);
	return (ret_str);
}

static int	s_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

static int	s_read(int fd, char *buffer, char *input)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, 1024);
	if (bytes_read == -1)
	{
		perror("read");
		close(fd);
		free(input);
		exit(1);
	}
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

static void	ft_strcpy(char *input, char *buffer)
{
    size_t iter;
    
	iter = 0;
	while (buffer[iter])
	{
		input[iter] = buffer[iter];
		iter++;
	}
}

char	*read_file_to_string(char *file_name)
{
	char	buffer[1025];
	int		fd;
	char	*input;
	int		bytes_read;
	size_t	input_len;

	
	input_len = 0;
	input = NULL;
	fd = s_open(file_name);
	while (1)
	{
		bytes_read = s_read(fd, buffer, input);
		if (bytes_read == 0)
			break ;
		input = ft_realloc(input, bytes_read + input_len);
		ft_strcpy(&input[input_len], buffer);
		input_len = ft_strlen(input);
	}
	close(fd);
	return (input);
}
