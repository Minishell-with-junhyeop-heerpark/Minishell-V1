/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:11:12 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/03 18:04:08 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	unsigned char	*str;

	str = (unsigned char *)buf;
	while (count--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return ((void *) NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main(int argc, char ** argv)
// {
//   char * result;

//   if ( argc != 2 )
//     printf( "Usage: %s string\n", argv[0] );
//   else
//   {
//     if ((result = (char *) memchr( argv[1], 'x', strlen(argv[1])) ) != NULL)
//       printf( "The string starting with x is %s\n", result );
//     else
//       printf( "The letter x cannot be found in the string\n" );
//   }
// }

// /********************  Output should be similar to:  **************

// The string starting with x is xing
// */