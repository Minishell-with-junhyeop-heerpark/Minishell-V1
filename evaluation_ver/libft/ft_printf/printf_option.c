/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:58:35 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/13 17:25:17 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_c(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_print_d(int d)
{
	char	*str;
	size_t	len;

	str = ft_itoa(d);
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

int	ft_print_u(unsigned int u)
{
	char	*str;
	size_t	len;

	str = ft_itoa_hex(u, 10, 0);
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

int	ft_print_s(char *s)
{
	int	i;

	if (s == NULL)
		return (ft_print_s("(null)"));
	i = 0;
	while (s[i] != 0)
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}
