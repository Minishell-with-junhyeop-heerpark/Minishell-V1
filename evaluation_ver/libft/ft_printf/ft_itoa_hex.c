/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:23:32 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/11 21:48:00 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_len_hex(unsigned long long n, int base)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

void	input_str_hex(char *str, unsigned long long adr, int base, int caps)
{
	int		s;
	int		i;
	char	buf[16];
	char	*digits;

	digits = "0123456789abcdef0123456789ABCDEF";
	s = 0;
	i = 0;
	if (adr == 0)
		buf[i++] = 0 + 48;
	while (adr)
	{
		buf[i++] = digits[adr % base + (base * caps)];
		adr /= base;
	}
	i--;
	while (i >= 0)
		str[s++] = buf[i--];
	str[s] = 0;
}

char	*ft_itoa_hex(unsigned long long adr, int base, int caps)
{
	int		len;
	char	*str;

	len = check_len_hex(adr, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	input_str_hex(str, adr, base, caps);
	return (str);
}
