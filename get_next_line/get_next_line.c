/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:48:42 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/30 14:25:41 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
char	*reader(int fd, char *container)
{
	ssize_t		i;
	char		*p;

	p = malloc(BUFFER_SIZE + 1);
	if (!p)
		return (NULL);
	i = 1;
	while (i != 0)
	{
		i = read(fd, p, BUFFER_SIZE);
		if (i == 0)
			break ;
		if (i == -1)
		{
			free(container);
			free(p);
			return (NULL);
		}
		p[i] = '\0';
		container = my_strjoin(container, p);
		if (checker(container))
			break ;
	}
	free(p);
	return (container);
}

char	*get_ligne(char *container)
{
	int		i;
	char	*p;

	i = 0;
	if (!container)
		return (NULL);
	while (container[i] && container[i] != '\n')
		i++;
	p = malloc(i + 2);
	if (!p)
		return (NULL);
	i = 0;
	while (container[i] && container[i] != '\n')
	{
		p[i] = container[i];
		i++;
	}
	if (container[i] == '\n')
		p[i++] = '\n';
	p[i] = '\0';
	return (p);
}

char	*cleaner(char *container)
{
	int		i;
	int		k;
	char	*p;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (!container[i] || (container[i] == '\n' && container[i + 1] == '\0'))
	{
		free(container);
		return (NULL);
	}
	p = malloc(my_strlen(container) - i);
	if (!p)
		return (NULL);
	i++;
	k = 0;
	while (container[i])
		p[k++] = container[i++];
	p[k] = '\0';
	free(container);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	container = reader(fd, container);
	if (!container)
		return (0);
	line = get_ligne(container);
	container = cleaner(container);
	return (line);
}

int	checker(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*my_strjoin(char *s1, char*s2)
{
	int		i;
	int		j;
	char	*p;
	int		len;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	len = my_strlen(s1) + my_strlen(s2);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s1 && s1[i])
		p[k++] = s1[i++];
	while (s2 && s2[j])
		p[k++] = s2[j++];
	p[k] = '\0';
	free(s1);
	return (p);
}

int	my_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}