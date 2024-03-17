/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:55:49 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/03 18:30:35 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*mem;

	if (num && size > ((size_t) 0 - 1) / num)
	{
		return (NULL);
	}
	mem = malloc((size) * num);
	if (!(mem))
		return (NULL);
	ft_bzero(mem, size * num);
	return (mem);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void) {
// 	if(ft_calloc(2147483647, 2147483647) == NULL) {
// 		printf("asdf");
// 	}
// }