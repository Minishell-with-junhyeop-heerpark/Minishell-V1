/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:17:22 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 15:10:57 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*f_dst;
	unsigned char	*f_src;
	size_t			i;

	f_dst = (unsigned char *)dst;
	f_src = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
	{	
		while (i < len)
		{
			f_dst[i] = f_src[i];
			i++;
		}
		return (dst);
	}
	i = len;
	while (i > 0)
	{
		f_dst[i - 1] = f_src[i - 1];
		i--;
	}
	return (dst);
}
