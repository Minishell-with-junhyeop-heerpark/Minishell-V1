/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:36:17 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 15:11:22 by heerpark         ###   ########.fr       */
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
