/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon < jihyjeon@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:11:48 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/02/21 17:58:00 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *fmt, ...);
int	format_printer(const char *s, va_list p);
int	char_printer(int c);
int	str_printer(char *s);
int	pointer_printer(unsigned long long n);
int	num_printer(long long n);
int	unsigned_printer(unsigned int n, char *base);
int	display(unsigned long long n, char *base, int nob);

#endif