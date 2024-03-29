/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:43:55 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/28 22:20:20 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	give_me_size(char const *s, unsigned int start, size_t len)
{
	if (start > (size_t)ft_strlen(s))
		return (0);
	else if (((size_t)ft_strlen(s) - start) < len)
		return ((ft_strlen(s) - start));
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	idx;

	if (!s)
		return (NULL);
	sub = (char *)malloc(give_me_size(s, start, len) + 1);
	if (!sub)
		return (NULL);
	if (start >= (size_t)ft_strlen(s))
	{
		sub[0] = '\0';
		return (sub);
	}
	idx = 0;
	while (idx < len && s[start])
	{
		sub[idx] = s[start];
		idx++;
		start++;
	}
	sub[idx] = '\0';
	return (sub);
}