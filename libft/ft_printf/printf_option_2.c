/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_option_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:45:52 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/13 17:24:58 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_p(unsigned long long p)
{
	char	*str;
	size_t	len;

	str = ft_itoa_hex(p, 16, 0);
	if (!str)
		return (-1);
	if (write(1, "0x", 2) == -1 || !ft_putstr(str))
	{
		free(str);
		return (-1);
	}
	len = ft_strlen(str) + 2;
	free(str);
	return ((int)len);
}

int	ft_print_sx(unsigned int x)
{
	char	*str;
	size_t	len;

	str = ft_itoa_hex((unsigned long long)x, 16, 0);
	if (!str)
		return (-1);
	if (!ft_putstr(str))
	{
		free(str);
		return (-1);
	}
	len = ft_strlen(str);
	free(str);
	return ((int)len);
}

int	ft_print_bx(unsigned int x)
{
	char	*str;
	size_t	len;

	str = ft_itoa_hex((unsigned long long)x, 16, 1);
	if (!str)
		return (-1);
	if (!ft_putstr(str))
	{
		free(str);
		return (-1);
	}
	len = ft_strlen(str);
	free(str);
	return ((int)len);
}
