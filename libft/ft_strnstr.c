/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:48:30 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/08 17:15:43 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cmp(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (s2[i] != 0)
	{
		if (!len--)
			return (0);
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != 0 && len--)
	{
		if (cmp(&haystack[i], needle, len + 1))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int main() {

// 	// char haystack[30] = "aaabcabcd";
// 	char needle[10] = "cd";
// 	printf("%s\n", strnstr(needle,0 , 0));
// }