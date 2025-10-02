/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:11:44 by jihyjeon          #+#    #+#             */
/*   Updated: 2025/10/02 14:00:58 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list		ptr;
	const char	*str;
	int			cnt;
	int			len;

	cnt = 0;
	len = 0;
	va_start(ptr, fmt);
	str = fmt - 1;
	while (*(++str))
	{
		if (*str != '%')
			len = char_printer(*str);
		else
		{
			len = format_printer(str, &ptr); // 포인터로 전달
			if (*(str + 1))
				str++;
		}
		if (len == -1)
			return (-1);
		cnt += len;
	}
	va_end(ptr);
	return (cnt);
}

int	format_printer(const char *s, va_list *p)
{
	char	c;
	int		len;

	c = *(s + 1);
	if (c == 'c')
		len = char_printer(va_arg(*p, int));
	if (c == 's')
		len = str_printer(va_arg(*p, char *));
	if (c == 'p')
		len = pointer_printer((unsigned long long)(uintptr_t)va_arg(*p, void *));
	if (c == 'd' || c == 'i')
		len = num_printer((long long)va_arg(*p, int));
	if (c == 'u')
		len = unsigned_printer(va_arg(*p, unsigned int), "0123456789");
	if (c == 'x')
		len = unsigned_printer(va_arg(*p, unsigned int), "0123456789abcdef");
	if (c == 'X')
		len = unsigned_printer(va_arg(*p, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		len = char_printer('%');
	return (len);
}

int	char_printer(int c)
{
	return (write(1, &c, 1));
}
