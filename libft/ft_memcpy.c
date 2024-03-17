/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:53:55 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/03 17:49:24 by junhyeop         ###   ########.fr       */
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

// #include<string.h>
// #include<stdio.h>

// int main(void)
// {
//     char src[] = "BlockDMask";
//     char dest1[] = "abcdefghijklmnop";
//     char dest2[] = "abcdefghijklmnop";

//     // 메모리 복사1 : src 길이만큼만 복사
//     memcpy(NULL, NULL, sizeof(char) * 10);

//     // 메모리 복사2 : src 길이 + 1 만큼 복사
//     ft_memcpy(NULL, NULL, sizeof(char) * 10);

//     // source
//     printf("src  : %s\n", src);

//     // destination
//     printf("dest1 : %s\n", dest1);
//     printf("dest2 : %s\n", dest2);

//     return 0;
// }