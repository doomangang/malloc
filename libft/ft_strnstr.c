/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:32 by jihyjeon          #+#    #+#             */
/*   Updated: 2023/11/07 17:48:02 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	uphere;
	char	*hays;

	hays = (char *)haystack;
	uphere = ft_min(len, ft_strlen(haystack)) - ft_strlen(needle) + 1;
	if (needle[0] == '\0')
		return (hays);
	if (!len)
		return (0);
	while (*hays && uphere--)
	{
		i = 0;
		while (*(hays + i) == *(needle + i))
		{
			i++;
			if (*(needle + i) == '\0')
				return (hays);
		}
		hays++;
	}
	return (0);
}
