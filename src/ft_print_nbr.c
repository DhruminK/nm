/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:30:49 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 16:30:49 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	ft_putnbr_helper(long nbr, int fd)
{
	int	ret;

	if (nbr > 9 || nbr < -9)
		ft_putnbr_helper(nbr / 10, fd);
	ret = nbr % 10;
	ret *= -1;
	ft_putchar_fd(ret + '0', fd);
}

void	ft_putnbr_fd(long nbr, int fd)
{
	if (nbr == 0)
		return (ft_putchar_fd('0', fd));
	if (nbr < 0)
		ft_putchar_fd('-', fd);
	ft_putnbr_helper(nbr, fd);
}

void	ft_print_hex_prefix(size_t nbr, uint8_t is_prefix,
			size_t num_len, int fd)
{
	size_t	i;
	size_t	j;
	char	c;

	if (is_prefix && nbr)
		write(fd, "0x", fd);
	i = 0;
	while ((nbr >> (i * 4)))
		i += 1;
	i = num_len - i;
	j = 0;
	while (++j <= i)
		write(fd, "0", 1);
	if (nbr)
		ft_puthex_fd(nbr, 0, fd);
}

void	ft_print_spaces(size_t num_len, int fd)
{
	size_t	i;

	i = 0;
	while (i < num_len)
	{
		write(fd, " ", 1);
		i += 1;
	}
}
