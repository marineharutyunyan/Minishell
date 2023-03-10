/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:37:49 by maharuty          #+#    #+#             */
/*   Updated: 2022/05/16 21:40:09 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	print_char(char c, int fd);
int	ft_printf(int fd, const char *s, ...);
int	print_pointer(uintptr_t ptr, int fd);
int	*print_hex(size_t num, char type, int fd);
int	*print_unsigned_number(unsigned int n, int fd);

#endif
