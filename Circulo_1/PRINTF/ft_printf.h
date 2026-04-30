/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:57:44 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/25 11:00:20 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <bsd/string.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int				ft_printf(char const *str, ...);
int				ft_putchar_int_fd(char c, int fd);
void			ft_one_digit(int *count, int fd, int n);
void			ft_one_unsigned_digit(unsigned int *count, int fd, int n);
int				ft_putnbr_int_fd(int n, int fd);
unsigned int	ft_putnbr_unint_fd(unsigned int n, int fd);
int				ft_putstr_int_fd(char *s, int fd);
int				ft_hex_low_fd(unsigned long n, int fd);
int				ft_hex_upp_fd(unsigned long n, int fd);
int				ft_ptr_fd(void *ptr, int fd);

// End of preprocessor directives / guards:
#endif // FT_PRINTF_H