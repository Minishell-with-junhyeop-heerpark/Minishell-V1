/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:43:03 by junhyeop          #+#    #+#             */
/*   Updated: 2023/11/13 17:16:36 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_print_sx(unsigned int x);
int		ft_print_bx(unsigned int x);
int		ft_print_u(unsigned int u);
int		ft_print_d(int d);
int		ft_print_p(unsigned long long p);
int		ft_print_s(char *s);
int		ft_print_c(int c);
int		ft_printf(const char *format, ...);
int		ft_putstr(char *s);
char	*ft_itoa(int n);
char	*ft_itoa_hex(unsigned long long hex, int base, int caps);
size_t	ft_strlen(const char *s);

#endif