/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:29:11 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 16:29:49 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	ft_find_sym_num(t_nm *nm, size_t *num_syms)
{
	Elf64_Shdr	*shdr;

	if (!nm || !num_syms)
		return (-1);
	*num_syms = 0;
	if (nm->sym_tab_info & SHDR_SYM_BIT)
	{
		shdr = (nm->shdr_tabs + SHDR_SYM);
		*num_syms += (shdr->sh_size / shdr->sh_entsize);
	}
	return (0);
}

static int	ft_parse_single_sym(uint8_t *inp, t_nm *nm, Elf64_Shdr *shdr,
		Elf64_Sym *sym)
{
	off_t	addr;

	if (!nm || !inp || !sym || !shdr)
		return (-1);
	addr = 0;
	ft_parse_elf_word(inp, &(sym->st_name), nm->is_little, &addr);
	if (shdr->sh_entsize == sizeof(Elf32_Shdr))
	{
		addr += (ft_parse_sym_section(inp + addr, &(sym->st_value), shdr, nm));
		addr += (ft_parse_sym_section(inp + addr, &(sym->st_size), shdr, nm));
	}
	sym->st_info = inp[addr++];
	sym->st_other = inp[addr++];
	ft_parse_elf_half(inp, &(sym->st_shndx), nm->is_little, &addr);
	if (shdr->sh_entsize != sizeof(Elf32_Shdr))
	{
		addr += (ft_parse_sym_section(inp + addr, &(sym->st_value), shdr, nm));
		addr += (ft_parse_sym_section(inp + addr, &(sym->st_size), shdr, nm));
	}
	return (0);
}

static int	ft_parse_single_sym_tab(Elf64_Shdr *shdr, Elf64_Sym *sym,
		char **name, t_nm *nm)
{
	size_t	i;
	uint8_t	j;
	size_t	len;
	off_t	offset;
	uint8_t	*inp;

	if (!shdr || !sym || !name || !nm)
		return (-1);
	j = SHDR_SYM_STR;
	if (shdr->sh_type == SHT_DYNSYM)
		j = SHDR_DYN_STR;
	inp = nm->file + (shdr->sh_offset);
	len = (shdr->sh_size / shdr->sh_entsize);
	offset = 0;
	i = 0;
	while (i < len)
	{
		ft_parse_single_sym(inp + offset, nm, shdr, sym + i);
		offset += shdr->sh_entsize;
		name[i] = (char *)(nm->tabs[j]) + sym[i].st_name;
		i += 1;
	}
	return (0);
}

int	ft_parse_sym_tabs(t_nm *nm)
{
	off_t	offset;
	int		ret;

	if (!nm || !nm->file)
		return (-1);
	if (ft_find_sym_num(nm, &(nm->num_syms)) == -1)
		return (-1);
	nm->syms = (Elf64_Sym *)malloc(sizeof(Elf64_Sym) * nm->num_syms);
	nm->sym_name = (char **)malloc(sizeof(char *) * nm->num_syms);
	if (!nm->syms || !nm->sym_name)
		return (-1);
	offset = 0;
	ret = 0;
	if (ret > -1 && (nm->sym_tab_info & SHDR_SYM_BIT))
		ret = ft_parse_single_sym_tab(nm->shdr_tabs + SHDR_SYM,
				nm->syms + offset, nm->sym_name + offset, nm);
	return (ret);
}
