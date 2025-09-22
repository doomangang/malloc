/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:29 by jihyjeon          #+#    #+#             */
/*   Updated: 2023/11/07 16:33:06 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*one;
	unsigned char	*two;

	if (!n)
		return (0);
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	while (n--)
	{
		if (*one != *two)
			return (*(unsigned char *)one - *(unsigned char *)two);
		one++;
		two++;
	}
	return (*(unsigned char *)(one - 1) - *(unsigned char *)(two - 1));
}
