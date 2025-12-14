/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphuwian <tphuwian@student.42bangkok.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-13 13:19:29 by tphuwian          #+#    #+#             */
/*   Updated: 2025-12-13 13:19:29 by tphuwian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*out;
	char		*rdreturn;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	rdreturn = (malloc(BUFFER_SIZE + 1));
	if (!rdreturn)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	out = readline(fd, &buffer[fd], rdreturn);
	clear(&rdreturn);
	return (out);
}

static char	*readline(int fd, char *buffer, char *rdreturn)
{
	ssize_t	bytesread;
	char	*temp;
	char	*newline;

	newline = ft_strchr(buffer, '\n');
	temp = NULL;
	bytesread = 0;
	while (!newline)
	{
		bytesread = read(fd, rdreturn, BUFFER_SIZE);
		if (bytesread < 0)
		{
			clear(buffer);
			return (NULL);
		}
		if (bytesread == 0)
			return (eoljoin(bytesread, buffer));
		rdreturn[bytesread] = 0;
		temp = ft_strjoin(*buffer, rdreturn);
		clear(buffer);
		*buffer = temp;
		newline = ft_strchr(*buffer, '\n');
	}
	return (eoljoin(newline - *buffer + 1, buffer));
}

static char	*eoljoin(ssize_t len, char **buffer)
{
	char	*out;
	char	*temp;

	temp = NULL;
	if (len <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		out = *buffer;
		*buffer = NULL;
		return (out);
	}
	temp = ft_substr(*buffer, len, BUFFER_SIZE);
	out = *buffer;
	out[len] = 0;
	*buffer = temp;
	return (out);
}

static void	clear(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}
