/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:42:31 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/03 18:01:53 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	if (dstsize == 0)
		return (ft_strlen(src));
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	while (src[i] != 0 && d_len + i + 1 < dstsize)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = 0;
	if (dstsize > d_len)
		return (s_len + d_len);
	return (s_len + dstsize);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
//     char s1[50] = "hello";
//     char s2[7] = "world";
//     char s3[50] = "hello";

//     size_t j = strlcat(s2, s1, 0);
//     printf("%zu\n", j);			// 10
//     printf("%s\n", s1);			// hellowo
//     j = ft_strlcat(0, s3, 0);
//     printf("%zu\n", j);			// 10
//     printf("%s\n", s3);			// hellowo
// }