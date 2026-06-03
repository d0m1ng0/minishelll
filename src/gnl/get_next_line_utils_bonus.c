/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anegorov <anegorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:18:41 by anegorov          #+#    #+#             */
/*   Updated: 2025/11/29 14:20:53 by anegorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_allclear(char *buf, char **rest_buf)
{
	if (buf)
		free(buf);
	if (*rest_buf)
		free(*rest_buf);
	*rest_buf = NULL;
	return (NULL);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char		*dest;
	size_t		len;
	size_t		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	char	*temp;

	if (!str)
		return (NULL);
	temp = (char *)str;
	while (*temp)
	{
		if (*temp == c)
			return (temp);
		temp++;
	}
	if (c == 0)
		return (temp);
	return (NULL);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*buf;

	buf = malloc(size * num);
	if (buf == NULL)
		return (NULL);
	size *= num;
	while (size--)
		((unsigned char *)buf)[size] = 0;
	return (buf);
}
