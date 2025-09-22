/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:46 by jihyjeon          #+#    #+#             */
/*   Updated: 2023/11/07 20:22:37 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	bytes;

	if (!count || !size)
		return (ft_calloc(1, 1));
	bytes = count * size;
	if (bytes / count != size)
		return (0);
	str = (void *)malloc(bytes);
	if (!(str))
		return (0);
	ft_bzero(str, count);
	return (str);
}
