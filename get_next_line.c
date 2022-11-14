/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:05 by lpires-n          #+#    #+#             */
/*   Updated: 2022/09/17 00:51:38 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char	*get_text(int fd, char *rest)
{
	int		number_readed;
	char	*tmp;
	char	*buffer;

	buffer = malloc(sizeof(char *) * (42 + 1));
	if (buffer == NULL)
		return (NULL);
	while (!ft_strchr(rest, '\n'))
	{
		number_readed = read(fd, buffer, 42);
		if (number_readed == 0 && *rest)
			break;
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
	static char	*rest;

	if (fd < 0 || 42 < 1)
		return (NULL);
	if (!rest)
		rest = ft_strdup("");
	rest = get_text(fd, rest);
	line = get_line(rest);
	if (line == NULL) 
		return (NULL);
	rest = ft_strdup(rest + ft_strlen(line));
	return (line);
}

int main(int argc , char **argv)
{
	int fd;
	char *linha;

	fd = open(argv[1], O_RDONLY);
	linha = get_next_line(fd);
	while (linha)
	{
		if (strnstr(linha, argv[2]))
			printf("%s\n", linha);
		free(linha);
		linha = get_next_line(fd);
	}
}