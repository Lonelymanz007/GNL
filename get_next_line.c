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

char *read_line(int fd, char *stash)
{
    char    *buffer;
    ssize_t bytes_read;
    char    *temp;

    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (!ft_strchr(stash, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        temp = stash;
        stash = ft_strjoin(stash, buffer);
        free(temp);
    }
    free(buffer);
    return (stash);
}
char *extract_line(char *stash)
{
    char    *line;
    size_t  i;
    if (!stash || stash[0] == '\0')
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    line = (char *)malloc(i + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
    {
        line[i] = stash[i];
        i++;
    }
    if (stash[i] == '\n')
    {
        line[i] = stash[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}
char *update_stash(char *stash)
{
    char    *new_stash;
    size_t  i;
    size_t  j;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (!stash[i])
    {
        free(stash);
        return (NULL);
    }
    i++;
    new_stash = (char *)malloc(ft_strlen(stash) - i + 1);
    if (!new_stash)
        return (NULL);
    j = 0;
    while (stash[i])
        new_stash[j++] = stash[i++];
    new_stash[j] = '\0';
    free(stash);
    return (new_stash);
}
char *get_next_line(int fd)
{
    static char *stash[FD_MAX];
    char        *line;
    if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
        return (NULL);
    stash[fd] = read_line(fd, stash[fd]);
    if (!stash[fd])
        return (NULL);
    line = extract_line(stash[fd]);
    stash[fd] = update_stash(stash[fd]);
    return (line);
}
