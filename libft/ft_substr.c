/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:43:06 by jihyjeon          #+#    #+#             */
/*   Updated: 2023/11/05 21:47:08 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len_cmp(char const *str, size_t len)
{
	size_t	str_l;

	str_l = ft_strlen(str);
	if (str_l <= len)
		return (str_l);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	r_len;

	if (ft_strlen(s) <= (size_t)start)
	{
		str = (char *)ft_calloc(sizeof(char), 1);
		*str = 0;
		return (str);
	}
	r_len = len_cmp(s + (size_t)start, len);
	str = (char *)ft_calloc(sizeof(char), r_len + 1);
	if (!(str))
		return (0);
	ft_strlcpy(str, s + (size_t)start, r_len + 1);
	return (str);
}
