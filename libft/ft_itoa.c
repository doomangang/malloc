/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:43:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2023/11/09 14:29:06 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_base(long long num, char *arr)
{
	if (num / 10 != 0)
		ft_itoa_base(num / 10, arr - 1);
	*arr = num % 10 + '0';
}

void	itgr_len(long long num, int *cnt)
{
	if (num < 0)
	{
		num *= -1;
		(*cnt)++;
	}
	if (num / 10 != 0)
	{
		(*cnt)++;
		itgr_len (num / 10, cnt);
	}
}

char	*ft_itoa(int n)
{
	char		*arr;
	int			cnt;
	long long	long_n;

	cnt = 1;
	long_n = (long long)n;
	itgr_len(long_n, &cnt);
	arr = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!arr)
		return (0);
	else if (long_n < 0)
	{
		*arr = '-';
		long_n *= -1;
	}
	ft_itoa_base(long_n, arr + cnt - 1);
	*(arr + cnt) = 0;
	return (arr);
}
