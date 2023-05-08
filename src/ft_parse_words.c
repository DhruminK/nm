/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:29:54 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/08 16:30:28 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_parse_elf_half(uint8_t *inp, uint16_t *half,
			int is_little, off_t *addr)
{
	if (!inp || !half || !addr)
		return ;
	ft_endian16(inp + *addr, half, is_little);
	*addr = *addr + 2;
}

void	ft_parse_elf_word(uint8_t *inp, uint32_t *word,
			int is_little, off_t *addr)
{
	if (!inp || !word || !addr)
		return ;
	ft_endian32(inp + *addr, word, is_little);
	*addr = *addr + 4;
}

void	ft_parse_elf_offset(uint8_t *inp, uint64_t *off,
			t_nm *nm, off_t *addr)
{
	uint32_t	off32;
	int			is_little;

	if (!inp || !off || !nm || !addr)
		return ;
	is_little = nm->elf_data == ELFDATA2LSB;
	if (nm->elf_class == ELFCLASS32)
	{
		ft_endian32(inp + *addr, &off32, is_little);
		*addr += 4;
		*off = (uint64_t)off32;
		return ;
	}
	ft_endian64(inp + *addr, off, is_little);
	*addr += 8;
}

void	ft_parse_shdr_xword(uint8_t *inp, uint64_t *off,
			t_nm *nm, off_t *addr)
{
	uint32_t	off32;

	if (!inp || !off || !nm || !addr)
		return ;
	if (nm->elf_hdr.e_shentsize == sizeof(Elf32_Shdr))
	{
		ft_endian32(inp + *addr, &off32, nm->is_little);
		*addr += 4;
		*off = (uint64_t)off32;
		return ;
	}
	ft_endian64(inp + *addr, off, nm->is_little);
	*addr += 8;
}

off_t	ft_parse_sym_section(uint8_t *inp, uint64_t *off,
			Elf64_Shdr *shdr, t_nm *nm)
{
	uint32_t	off32;

	if (!inp || !off || !nm || !shdr)
		return (0);
	if (shdr->sh_entsize == sizeof(Elf32_Sym))
	{
		ft_endian32(inp, &off32, nm->is_little);
		*off = (uint64_t)off32;
		return (4);
	}
	ft_endian64(inp, off, nm->is_little);
	return (8);
}
