/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:55:49 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/28 15:03:26 by heerpark         ###   ########.fr       */
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
