/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:55:14 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/05 19:32:36 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int c)
{
	while (*string)
	{
		if (*string == (char)c)
			return ((char *)string);
		string++;
	}
	if (*string == (char)c)
		return ((char *)string);
	return ((char *) NULL);
}

// #include <stdio.h>
// #include <string.h>

// #define SIZE 40

// int main(void)
// {
// 	char buffer1[SIZE] = "computer program";
// 	char * ptr;
// 	int    ch = 'z';

// 	ptr = ft_strchr( buffer1, 't' + 256 );
// 	printf( "The first occurrence of %c in '%s' is '%s'\n",ch, buffer1, ptr );

// }

/*****************  Output should be similar to:  *****************

The first occurrence of p in 'computer program' is 'puter program'
*/