/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:16:34 by anegorov          #+#    #+#             */
/*   Updated: 2026/01/09 17:52:47 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Created: 2025/11/23 21:52:00 by anegorov          #+#    #+#             */
/*   Updated: 2025/11/29 14:13:44 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_cat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;
	char	*temp_dest;

	temp_dest = dest;
	dest = ft_calloc(ft_strlen(dest) + ft_strlen(src) + 1, sizeof(char));
	if (!dest)
	{
		if (temp_dest)
			free(temp_dest);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (temp_dest && temp_dest[j])
	{
		dest[j] = temp_dest[j];
		j++;
	}
	while (src && src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	if (temp_dest)
		free(temp_dest);
	return (dest);
}

char	*ft_read(int fd, char *rest_buf)
{
	char		*buf;
	size_t		rd;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (ft_allclear(buf, &rest_buf));
	rd = 1;
	if (!ft_strchr(rest_buf, '\n'))
		rd = read(fd, buf, BUFFER_SIZE);
	while (!ft_strchr(rest_buf, '\n') && rd > 0)
	{
		if (ft_strchr(rest_buf, '\n'))
			buf[0] = '\0';
		else
			buf[rd] = '\0';
		rest_buf = ft_cat(rest_buf, buf);
		if (!rest_buf)
			return (ft_allclear(buf, &rest_buf));
		if (!ft_strchr(rest_buf, '\n'))
			rd = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (rest_buf);
}

char	*ft_getrestbuf(char *rest_buf)
{
	char	*next;
	char	*temp;

	if (!rest_buf || !*rest_buf)
		next = NULL;
	else
		next = ft_strchr(rest_buf, '\n');
	if (!next)
	{
		if (rest_buf)
			free(rest_buf);
		return (NULL);
	}
	temp = ft_strdup(next + 1);
	if (!temp)
		return (ft_allclear(NULL, &rest_buf));
	free(rest_buf);
	rest_buf = temp;
	return (rest_buf);
}

char	*ft_getline(char *rest_buf)
{
	char	*line;
	char	*next;
	int		len;
	int		i;

	if (!rest_buf || !*rest_buf)
		return (NULL);
	next = ft_strchr(rest_buf, '\n');
	if (!next && rest_buf && *rest_buf)
		return (ft_strdup(rest_buf));
	else if (!next)
		return (NULL);
	len = ft_strlen(rest_buf);
	i = 0;
	if (next)
		len -= (ft_strlen(next) - 1);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (rest_buf && *rest_buf && i < len)
		line[i++] = *(rest_buf++);
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest_buf[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (rest_buf[fd])
		{
			free(rest_buf[fd]);
			rest_buf[fd] = NULL;
		}
		return (NULL);
	}
	rest_buf[fd] = ft_read(fd, rest_buf[fd]);
	if (!rest_buf[fd])
		return (NULL);
	line = ft_getline(rest_buf[fd]);
	rest_buf[fd] = ft_getrestbuf(rest_buf[fd]);
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <time.h>
// #define FILE_COUNT 4
// #define MAX_FD 4
// int main(void)
// {
//     const char *files[FILE_COUNT] = {
//         "small.txt",
//         "medium.txt",
//         "big.txt",
//         "empty.txt"
//     };
//     int fds[MAX_FD];
//     int alive[MAX_FD];
//     char *line;
//     int i;
//     int active = MAX_FD;
//     srand(time(NULL));
//     for (i = 0; i < MAX_FD; i++)
//     {
//         fds[i] = open(files[i], O_RDONLY);
//         if (fds[i] < 0)
//         {
//             perror("open");
//             return 1;
//         }
//         alive[i] = 1;
//     }
//     printf("=== RANDOM FD TEST ===\n");
//     while (active > 0)
//     {
//         i = rand() % MAX_FD;
//         if (!alive[i])
//             continue;
//         line = get_next_line(fds[i]);
//         if (line)
//         {
//             printf("[fd %d | %s] %s", i, files[i], line);
//             free(line);
//         }
//         else
//         {
//             close(fds[i]);
//             alive[i] = 0;
//             active--;
//             printf("[fd %d | %s] EOF\n", i, files[i]);
//         }
//     }
//     return 0;
// }
