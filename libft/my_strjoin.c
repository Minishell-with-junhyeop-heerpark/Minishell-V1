/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:34:35 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/25 19:53:22 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	my_strjoin(char **s1, char *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*str;

	tmp = *s1;
	if (!tmp || !s2)
		return ;
	i = 0;
	j = 0;
	len = ft_strlen((char *)tmp) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return ;
	while (tmp[j])
		str[i++] = tmp[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	free(tmp);
	free(s2);
	*s1 = str;
}
