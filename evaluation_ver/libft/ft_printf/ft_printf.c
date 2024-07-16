/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:50:14 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/13 17:32:43 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(const char c, va_list ap)
{
	if (c == 'c')
		return (ft_print_c(va_arg(ap, int)));
	else if (c == 's')
		return (ft_print_s(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_print_p(va_arg(ap, unsigned long long)));
	else if (c == 'd' || c == 'i')
		return (ft_print_d(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_print_u(va_arg(ap, unsigned int)));
	else if (c == 'x')
		return (ft_print_sx(va_arg(ap, unsigned int)));
	else if (c == 'X')
		return (ft_print_bx(va_arg(ap, unsigned int)));
	else if (c == '%')
		return (ft_print_c('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		idx;
	int		len;
	int		cnt;
	va_list	ap;

	va_start(ap, format);
	idx = 0;
	cnt = 0;
	while (format[idx])
	{
		if (format[idx] == '%')
			len = check_type(format[++idx], ap);
		else if (format[idx])
			len = ft_print_c(format[idx]);
		if (len < 0)
			return (-1);
		cnt += len;
		idx++;
	}
	va_end(ap);
	return (cnt);
}
