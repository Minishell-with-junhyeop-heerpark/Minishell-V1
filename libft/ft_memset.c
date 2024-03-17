/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:10:29 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/03 17:47:59 by junhyeop         ###   ########.fr       */
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

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	void *dest = " ";
// 	if (ft_memset(dest, 0, 0) == NULL)
// 		printf("sdaf");
// }