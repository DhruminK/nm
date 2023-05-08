/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_nm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:36:18 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 17:50:34 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	ft_is_alphanum(char n)
{
	if (n >= 'A' && n <= 'Z')
		return (1);
	if (n >= 'a' && n <= 'z')
		return (1);
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}

static size_t	ft_skip_non_alphanum(char *n, size_t *num_skip)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (n[i] && !ft_is_alphanum(n[i]))
		i += 1;
	if (num_skip)
		*num_skip += i;
	return (i);
}

static int	ft_char_cmp(char n1, char n2)
{
	if (n1 >= 'A' && n1 <= 'Z')
		n1 = n1 - 'A' + 'a';
	if (n2 >= 'A' && n2 <= 'Z')
		n2 = n2 - 'A' + 'a';
	return (n1 - n2);
}

static int	ft_sys_cmp_helper(char **n1, char **n2, size_t *num_skip)
{
	int	ret;

	*n1 += ft_skip_non_alphanum(*n1, num_skip);
	*n2 += ft_skip_non_alphanum(*n2, num_skip + 1);
	ret = ft_char_cmp(**n1, **n2);
	if (ret)
		return (ret);
	*n1 += 1;
	*n2 += 1;
	return (0);
}

int	ft_sys_cmp(char *arg1, char *arg2, int *ret)
{
	size_t	num_skip[2];
	char	*n1;
	char	*n2;

	if (!arg1 || !arg2 || !ret)
		return (-1);
	ft_memset(num_skip, 0, sizeof(size_t) * 2);
	*ret = 0;
	n1 = arg1;
	n2 = arg2;
	while (*arg1 && *arg2 && !*ret)
		*ret = ft_sys_cmp_helper(&arg1, &arg2, (size_t *)num_skip);
	if (!*ret && ((!*arg1 && *arg2) || (*arg1 && !*arg2)))
		*ret = (*arg1 - *arg2);
	if (*ret)
		return (0);
	if (num_skip[0] > num_skip[1])
		*ret = -1;
	else if (num_skip[0] < num_skip[1])
		*ret = 1;
	return (0);
}
