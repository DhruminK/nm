/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_syms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:35:34 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 18:04:56 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	ft_sym_swap(Elf64_Sym *sym1, char **sn1,
				Elf64_Sym *sym2, char **sn2)
{
	char		*tmp;
	Elf64_Sym	tmp_sym;

	if (!sym1 || !sym2 || !sn1 || !sn2)
		return ;
	ft_memcpy(&tmp_sym, sym1, sizeof(Elf64_Sym));
	ft_memcpy(sym1, sym2, sizeof(Elf64_Sym));
	ft_memcpy(sym2, &tmp_sym, sizeof(Elf64_Sym));
	tmp = *sn1;
	*sn1 = *sn2;
	*sn2 = tmp;
}

void	ft_sort_syms(Elf64_Sym *syms, char **sym_names,
		size_t num_syms, t_nm *nm)
{
	size_t	i;
	size_t	j;
	int		ret;

	i = 0;
	while (i < num_syms)
	{
		j = 0;
		while (j < num_syms - 1)
		{
			ret = ft_strcmp(sym_names[j], sym_names[j + 1]);
			if (ret > 0)
				ft_sym_swap(syms + j, sym_names + j,
					syms + j + 1, sym_names + j + 1);
			j += 1;
		}
		i += 1;
	}
}
