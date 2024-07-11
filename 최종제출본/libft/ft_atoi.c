/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:48 by junhyeop          #+#    #+#             */
/*   Updated: 2024/02/02 19:36:40 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	if (*str == 0 || ft_strlen(str) > 11)
		return (0);
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	if (*str < '0' || *str > '9')
		return (0);
	while (*str != 0)
	{
		if (*str < '0' || *str > '9')
			return (0);
		res = (res * 10) + (*str++ - 48) * (sign);
		if (res < -2147483648 || res > 2147483647)
			return (0);
	}
	return (res);
}
