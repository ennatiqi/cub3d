/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:37:30 by aachfenn          #+#    #+#             */
/*   Updated: 2023/11/02 21:44:14 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
