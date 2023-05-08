/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:30:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 16:30:33 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i += 1;
	write(fd, str, i);
}

void	ft_putnstr_fd(char *str, size_t n, int fd)
{
	write(fd, str, n);
}

void	ft_putunbr_fd(size_t nbr, int fd)
{
	if (nbr == 0)
		return (ft_putchar_fd('0', fd));
	if (nbr > 9)
		ft_putunbr_fd(nbr / 10, fd);
	ft_putchar_fd((nbr % 10) + '0', fd);
}

void	ft_puthex_fd(size_t nbr, uint8_t is_prefix, int fd)
{
	if (!nbr)
		return (ft_putchar_fd('0', fd));
	if (is_prefix)
		ft_putstr_fd("0x", fd);
	if (nbr > 15)
		ft_puthex_fd(nbr >> 4, 0, fd);
	if ((nbr & 0xF) > 9)
		return (ft_putchar_fd((nbr & 0xF) - 10 + 'a', fd));
	ft_putchar_fd((nbr & 0xF) + '0', fd);
}
