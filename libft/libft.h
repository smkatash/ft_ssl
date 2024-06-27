/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:30:19 by aiarinov          #+#    #+#             */
/*   Updated: 2024/06/27 15:00:21 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdbool.h>

void	*ft_memset(void *str, int value, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *str1);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char    **ft_append_array(const char* str, char** arr);

#endif
