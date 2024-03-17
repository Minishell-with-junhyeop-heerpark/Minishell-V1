/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:43:55 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/05 19:53:03 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	idx;
	char	*substr;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start || len == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (slen - start <= len)
		return (ft_strdup(s + start));
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	idx = 0;
	while (idx < len && s[idx + start] != 0)
	{
		substr[idx] = s[idx + start];
		idx++;
	}
	substr[idx] = 0;
	return (substr);
}

// #include <stdio.h>
// #include <string.h>
// int main(){
// 	char * s = ft_substr("tripouille", 0, 42000);

// 	// printf("%zu\n", strlen(s));
// 	// printf("%s\n", s);

// 	s = ft_substr("tripouille", 1, 1);

// 	printf("%zu\n", strlen(s));
// 	printf("%s\n", s);
// }