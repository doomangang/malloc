/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:18 by jihyjeon          #+#    #+#             */
/*   Updated: 2023/11/05 22:12:05 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	idx;

	idx = 0;
	len = ft_strlen(s) + 1;
	while (idx != len)
	{
		if (*(s + idx) == (char)c)
			return ((char *)(s + idx));
		idx++;
	}
	return (0);
}
