/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_sym_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:34:30 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 17:36:57 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	ft_strcmp_case(char *n1, char *n2)
{
	size_t	i;
	char	c1;
	char	c2;

	i = 0;
	while (n1[i] && n2[i])
	{
		c1 = n1[i];
		c2 = n2[i];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 = c1 - 'A' + 'a';
		if (c2 >= 'A' && c2 <= 'Z')
			c2 = c2 - 'A' + 'a';
		if (c1 != c2)
			return (c1 - c2);
		i += 1;
	}
	return (n1[i] - n2[i]);
}

int	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i += 1;
	return (i);
}

int	ft_strncmp(char *n1, char *n2, size_t n)
{
	size_t	i;

	if (!n1 && !n2)
		return (0);
	else if (!n1 && n2)
		return (-n2[0]);
	else if (n1 && !n2)
		return (n1[0]);
	i = 0;
	while (i < n && n1[i] && n2[i])
	{
		if (n1[i] != n2[i])
			return (n1[i] - n2[i]);
		i += 1;
	}
	return (0);
}

static int	ft_print_sym_type_caps2(t_nm_sym_type se, uint8_t is_caps)
{
	if (se == NM_ST_BSS_SECTION && !is_caps)
		write(1, "b", 1);
	else if (se == NM_ST_BSS_SECTION)
		write(1, "B", 1);
	else if (se == NM_ST_UNDEF_SECTION)
		write(1, "U", 1);
	else if (se == NM_ST_UNIQUE_SECTION)
		write(1, "u", 1);
	else if (se == NM_ST_WEAK_OBJ_SECTION && is_caps)
		write(1, "V", 1);
	else if (se == NM_ST_WEAK_OBJ_SECTION)
		write(1, "v", 1);
	return (1);
}

int	ft_print_sym_type_caps(t_nm_sym_type se, uint8_t is_caps)
{
	if (se == NM_ST_TEXT_SECTION && is_caps)
		write(1, "T", 1);
	else if (se == NM_ST_TEXT_SECTION)
		write(1, "t", 1);
	else if (se == NM_ST_RO_DATA_SECTION && is_caps)
		write(1, "R", 1);
	else if (se == NM_ST_RO_DATA_SECTION)
		write(1, "r", 1);
	else if (se == NM_ST_INIT_DATA_SECTION && is_caps)
		write(1, "D", 1);
	else if (se == NM_ST_INIT_DATA_SECTION)
		write(1, "d", 1);
	else if (se == NM_ST_WEAK_SECTION && is_caps)
		write(1, "W", 1);
	else if (se == NM_ST_WEAK_SECTION)
		write(1, "w", 1);
	return (ft_print_sym_type_caps2(se, is_caps));
}
