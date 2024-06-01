/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:11:12 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 15:10:37 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	unsigned char	*str;

	str = (unsigned char *)buf;
	while (count--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return ((void *) NULL);
}
