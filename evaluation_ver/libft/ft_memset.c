/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:10:29 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 15:11:00 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	unsigned char	*f_dest;
	size_t			i;

	i = 0;
	f_dest = (unsigned char *)dest;
	while (i < count)
		f_dest[i++] = (unsigned char)c;
	return ((void *)f_dest);
}
