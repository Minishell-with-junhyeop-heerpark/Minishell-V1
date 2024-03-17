/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:36:17 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/08 17:16:52 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int c)
{
	const char	*last;

	last = NULL;
	while (*string)
	{
		if (*string == (unsigned char)c)
			last = string;
		string++;
	}
	if (*string == (unsigned char) c)
		return ((char *)string);
	return ((char *)last);
}

// #include <stdio.h>
// #include <string.h>
// int main(void){
// 		char s2[] = "ltripouiel";
// 		printf("%s",strrchr(s2, 'e'));
// }