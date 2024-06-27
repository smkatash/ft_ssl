/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 07:56:11 by ktashbae          #+#    #+#             */
/*   Updated: 2024/06/22 17:53:28 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strlcpy_d(char *str, char *s1, char *s2, size_t pref)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = pref;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[count] = s2[i];
		i++;
		count++;
	}
	str[count] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	pref;
	size_t	suff;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	pref = ft_strlen(s1);
	suff = ft_strlen(s2);
	str = malloc(sizeof(char) * (pref + suff + 1));
	if (str)
	{
		ft_strlcpy_d(str, (char *)s1, (char *)s2, pref);
		return (str);
	}
	return (NULL);
}
