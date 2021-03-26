/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:13:10 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/26 12:05:57 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[len] != '\n' && remainder[len] != '\0')
		len++;
	if (!remainder[len])
	{
		free(remainder);
		return (NULL);
	}
	if (!(new_remainder = malloc(sizeof(char) * ((ft_strlen(remainder) - len) +
			1))))
		return (NULL);
	len++;
	while (remainder[len] != '\0')
		new_remainder[i++] = remainder[len++];
	new_remainder[i] = '\0';
	free(remainder);
	return (new_remainder);
}

char	*take_line_from_remainder(const char *str)
{
	int		i;
	int		len;
	char	*tmp;

	len = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[len] != '\n' && str[len] != '\0')
		len++;
	if (!(tmp = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	char			*buffer;
	int				bytes;
	static	char	*remainder;

	bytes = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!newline(remainder) && bytes != 0)
	{
		if ((bytes = read(fd, buffer, BUFFER_SIZE)) == -1)
				return (-1);
		buffer[bytes] = '\0';
		if (!(remainder = ft_strjoin(remainder, buffer)))
			return (-1);
	}
	free(buffer);
	if (!(*line = take_line_from_remainder(remainder)))
		return (-1);
	if (!(remainder = update_remainder(remainder)))
		return (0);
	return (1);
}

int		main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("text", O_RDONLY);
	while ((i = get_next_line(fd, &line)))
	{
		printf("%d %s\n", i, line);
		free(line);
	}
	i = get_next_line(fd, &line);
	printf("%d %s\n", i, line);
	return (0);
}
