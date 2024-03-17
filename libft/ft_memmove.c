/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:17:22 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/03 17:48:46 by junhyeop         ###   ########.fr       */
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

// #include<string.h>
// #include<stdio.h>

// int main(void)
// {
//         char array[10];

//         memset(array, 0, sizeof(array));
//         strcpy(array, "test");

//         printf("original : %s\n", array);

//         ft_memmove(array+2, array, strlen("test"));

//         printf("after memmove : %s\n", array);

//         return 0;
// }