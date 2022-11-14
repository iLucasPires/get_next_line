/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:05 by lpires-n          #+#    #+#             */
/*   Updated: 2022/06/22 18:53:42 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_text(int fd, char *rest)
{
	int		number_readed;
	char	*tmp;
	char	*buffer;

	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (!ft_strchr(rest, '\n'))
	{
		number_readed = read(fd, buffer, BUFFER_SIZE);
		if (number_readed == 0 && *rest)
			break ;
		if (number_readed <= 0)
		{
			free(rest);
			free(buffer);
			return (NULL);
		}
		buffer[number_readed] = '\0';
		tmp = rest;
		rest = ft_strjoin(rest, buffer);
		free(tmp);
	}
	free(buffer);
	return (rest);
}

char	*get_line(char *rest)
{
	char	*line;
	int		counter;

	counter = 0;
	if (!rest)
	{
		free(rest);
		return (NULL);
	}
	while (rest[counter] != '\n' && rest[counter] != '\0')
		counter++;
	line = (char *)malloc(sizeof(char *) * (counter + 1));
	ft_strlcpy(line, rest, counter + 2);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	*rest[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!rest[fd])
		rest[fd] = ft_strdup("");
	rest[fd] = get_text(fd, rest[fd]);
	line = get_line(rest[fd]);
	if (line == NULL)
		return (NULL);
	tmp = rest[fd];
	rest[fd] = ft_strdup(rest[fd] + ft_strlen(line));
	free(tmp);
	return (line);
}
