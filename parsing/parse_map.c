/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jromann <jromann@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:11:39 by jromann           #+#    #+#             */
/*   Updated: 2026/01/06 16:11:07 by jromann          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free2d(char **str)
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

int	valid_char(char c)
{
	if (c != '1' && c != ' ')
		return (1);
	else
		return (0);
}

int	should_be_a_wall(t_user *user, size_t x, size_t y)
{
	size_t	line_len_above;
	size_t	line_len_below;

	if (x == 0 || y == 0)
		return (valid_char(user->map[y][x]));
	if (user->map[y + 1] == NULL || user->map[y][x + 1] == '\0')
		return (valid_char(user->map[y][x]));
	line_len_above = ft_strlen(user->map[y - 1]);
	line_len_below = ft_strlen(user->map[y + 1]);
	if (line_len_above <= x + 1 || line_len_below <= x + 1)
		return (valid_char(user->map[y][x]));
	if (user->map[y - 1][x] == ' ' || user->map[y + 1][x] == ' ')
		return (valid_char(user->map[y][x]));
	if (user->map[y - 1][x + 1] == ' ' || user->map[y + 1][x + 1] == ' ')
		return (valid_char(user->map[y][x]));
	if (user->map[y - 1][x - 1] == ' ' || user->map[y + 1][x - 1] == ' ')
		return (valid_char(user->map[y][x]));
	if (user->map[y][x - 1] == ' ' || user->map[y][x + 1] == ' ')
		return (valid_char(user->map[y][x]));
	return (0);
}

int	valid_line(t_user *user, size_t pos)
{
	size_t	iter;

	iter = 0;
	while (user->map[pos][iter])
	{
		if (user->map[pos][iter] != ' ' && user->map[pos][iter] != '1'
			&& user->map[pos][iter] != '0')
		{
			if ((user->map[pos][iter] == 'N' || user->map[pos][iter] == 'S'
					|| user->map[pos][iter] == 'E'
					|| user->map[pos][iter] == 'W') && user->start_dir == 'D')
				user->start_dir = user->map[pos][iter];
			else
				return (1);
		}
		if (should_be_a_wall(user, iter, pos) == 1)
			return (1);
		iter++;
	}
	return (0);
}

void	check_format(char *name)
{
	size_t	iter;

	iter = 0;
	while (name[iter])
		iter++;
	if (iter < 5)
	{
		write(2, "Error\nWrong format !\n", 21);
		exit(1);
	}
	if (ft_strncmp(".cub", &name[iter - 4], 4) != 0)
	{
		write(2, "Error\nWrong format !\n", 21);
		exit(1);
	}
}

bool	is_empty_line(char *line)
{
	size_t	iter;

	iter = 0;
	while (line[iter] == 32)
		iter++;
	if (line[iter] == '\n')
		return (true);
	return (false);
}

void	skip_whitspaces(char *str, size_t *iter)
{
	while (str[*iter] == 32)
		iter++;
}

void	check_empty_lines(char *map)
{
	size_t	iter;
	bool	empty_line;

	empty_line = false;
	iter = 0;
	while (map[iter])
	{
		if (is_empty_line(&map[iter]))
			empty_line = true;
		else
		{
			if (empty_line == true)
			{
				write(2, "Error\nEmpty line in map !\n", 26);
				exit(1);
			}
		}
		while (map[iter] != '\n' && map[iter])
			iter++;
		if (map[iter] != '\0')
			iter++;
	}
}

size_t	map_exists(char *input)
{
	size_t	iter;
	size_t	offset;

	iter = 0;
	while (input[iter])
	{
		if (input[iter] == '\n')
		{
			iter++;
			offset = 0;
			while (input[iter + offset] == 32)
				offset++;
			if (input[iter + offset] == '1')
				return (iter);
		}
		else
			iter++;
	}
	write(2, "Error\nNo map found !\n", 21);
	exit(1);
}

void	initialise_data(char *input, t_user *user)
{
	size_t	iter;

	iter = map_exists(input);
	check_empty_lines(&input[iter]);
	user->start_dir = 'D';
	user->info = ft_split(input, '\n');
	user->map = ft_split(&input[iter], '\n');
	if (user->map == NULL)
	{
		perror("initialise_data");
		exit(1);
	}
}

void	valid_input(t_user *user)
{
	size_t	iter;

	iter = 0;
	while (user->map[iter])
	{
		if (valid_line(user, iter) == 1)
		{
			write(2, "Error\nInvalid input !\n", 22);
			free2d(user->map);
			exit(1);
		}
		iter++;
	}
}

char	*ft_realloc(char *in_str, size_t size)
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

char	*open_arg(char *file_name)
{
	char	buffer[1025];
	int		bytes_read;
	char	*input;
	size_t	input_len;
	int		fd;
	size_t	iter;

	input_len = 0;
	input = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	while (1)
	{
		bytes_read = read(fd, buffer, 1024);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		input = ft_realloc(input, bytes_read + input_len);
		iter = 0;
		while (buffer[iter])
		{
			input[input_len + iter] = buffer[iter];
			iter++;
		}
		input_len = ft_strlen(input);
	}
	if (bytes_read == -1)
	{
		perror("read");
		close(fd);
		free(input);
		exit(1);
	}
	close(fd);
	return (input);
}

void	extract_color(t_user *user, int flag, size_t pos)
{
	char	red[4];
	char	blue[4];
	char	green[4];
	size_t	digit;
	size_t	iter;
	size_t	color_digit;

	digit = 0;
	iter = 1;
	color_digit = 0;
	if (flag == FLOOR)
	{
		if (user->floor.blue != -1)
		{
			write(2, "Error\nInvalid input !\n", 22);
			exit(1);
		}
		while (user->info[pos][iter] == ' ')
			iter++;
		while (user->info[pos][iter])
		{
			if (user->info[pos][iter] == ',')
			{
				iter++;
				digit++;
				color_digit = 0;
				if (digit > 3)
					exit(1);
			}
			while (user->info[pos][iter] == ' ')
				iter++;
			if (!ft_isdigit(user->info[pos][iter]))
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			if (digit == 0)
				red[color_digit] = user->info[pos][iter];
			if (digit == 1)
				blue[color_digit] = user->info[pos][iter];
			if (digit == 2)
				green[color_digit] = user->info[pos][iter];
			color_digit++;
			if (color_digit > 3)
				exit(1);
			if (digit == 0)
				red[color_digit] = '\0';
			if (digit == 1)
				blue[color_digit] = '\0';
			if (digit == 2)
				green[color_digit] = '\0';
			iter++;
		}
		user->floor.red = ft_atoi(red);
		user->floor.blue = ft_atoi(blue);
		user->floor.green = ft_atoi(green);
		if (user->floor.red > 255 || user->floor.blue > 255
			|| user->floor.green > 255)
		{
			write(2, "Error\nInvalid input !\n", 22);
			exit(1);
		}
	}
	if (flag == CEILING)
	{
		if (user->ceiling.blue != -1)
		{
			write(2, "Error\nInvalid input !\n", 22);
			exit(1);
		}
		while (user->info[pos][iter] == ' ')
			iter++;
		while (user->info[pos][iter])
		{
			if (user->info[pos][iter] == ',')
			{
				iter++;
				digit++;
				color_digit = 0;
				if (digit > 3)
					exit(1);
			}
			while (user->info[pos][iter] == ' ')
				iter++;
			if (!ft_isdigit(user->info[pos][iter])
				&& user->info[pos][iter] != ' ')
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			if (digit == 0)
				red[color_digit] = user->info[pos][iter];
			if (digit == 1)
				blue[color_digit] = user->info[pos][iter];
			if (digit == 2)
				green[color_digit] = user->info[pos][iter];
			color_digit++;
			if (color_digit > 3)
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			if (digit == 0)
				red[color_digit] = '\0';
			if (digit == 1)
				blue[color_digit] = '\0';
			if (digit == 2)
				green[color_digit] = '\0';
			iter++;
		}
		user->ceiling.red = ft_atoi(red);
		user->ceiling.blue = ft_atoi(blue);
		user->ceiling.green = ft_atoi(green);
		if (user->ceiling.red > 255 || user->ceiling.blue > 255
			|| user->ceiling.green > 255)
		{
			write(2, "Error\nInvalid input !\n", 22);
			exit(1);
		}
	}
}

void	extract_line(t_user *user, size_t pos, int flag)
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
	if (flag == NO)
		user->no_path = &user->info[pos][start];
	if (flag == SO)
		user->so_path = &user->info[pos][start];
	if (flag == WE)
		user->we_path = &user->info[pos][start];
	if (flag == EA)
		user->ea_path = &user->info[pos][start];
}

void	extract_info(t_user *user)
{
	size_t	iter;
	size_t	iter2;
	size_t	offset;

	iter = 0;
	user->we_path = NULL;
	user->so_path = NULL;
	user->ea_path = NULL;
	user->no_path = NULL;
	user->floor.red = -1;
	user->floor.blue = -1;
	user->floor.green = -1;
	user->ceiling.red = -1;
	user->ceiling.blue = -1;
	user->ceiling.green = -1;
	while (user->info[iter])
	{
		iter2 = 0;
		offset = 0;
		if (ft_strncmp("NO ", user->info[iter], 3) == 0)
		{
			if (user->no_path != NULL)
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			extract_line(user, iter, NO);
		}
		else if (ft_strncmp("SO ", user->info[iter], 3) == 0)
		{
			if (user->so_path != NULL)
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			extract_line(user, iter, SO);
		}
		else if (ft_strncmp("WE ", user->info[iter], 3) == 0)
		{
			if (user->we_path != NULL)
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			extract_line(user, iter, WE);
		}
		else if (ft_strncmp("EA ", user->info[iter], 3) == 0)
		{
			if (user->ea_path != NULL)
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			extract_line(user, iter, EA);
		}
		else if (ft_strncmp("F", user->info[iter], 1) == 0)
			extract_color(user, FLOOR, iter);
		else if (ft_strncmp("C", user->info[iter], 1) == 0)
			extract_color(user, CEILING, iter);
		else if (user->info[iter][iter2] == ' '
			|| user->info[iter][iter2] == '1')
		{
			while (user->info[iter][iter2] == ' ')
				iter2++;
			if (user->info[iter][iter2] != '1')
			{
				write(2, "Error\nInvalid input !\n", 22);
				exit(1);
			}
			else
				return ;
		}
		else
		{
			write(2, "Error\nInvalid input !\n", 22);
			exit(1);
		}
		iter++;
	}
}

int	parse_map(char *file_name, t_user *user)
{
	char *input;

	validate_file_extension(file_name);
	input = read_file_to_string(file_name);
	initialise_data(input, user);
	extract_info(user);
	valid_input(user);
	printf("%d\n", user->ceiling.red);
	return (0);
}