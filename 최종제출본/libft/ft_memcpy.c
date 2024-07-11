/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:53:55 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 15:10:52 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*f_dst;
	unsigned char	*f_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	f_dst = (unsigned char *)dst;
	f_src = (unsigned char *)src;
	while (n--)
	{
		*f_dst++ = *f_src++;
	}
	return (dst);
}
