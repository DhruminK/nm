#include "ft_nm.h"

int	ft_extract_single_shdr(uint8_t *inp, t_nm *nm, Elf64_Shdr *shdr)
{
	off_t	addr;

	if (!inp || !nm || !shdr)
		return (-1);
	addr = 0;
	ft_parse_elf_word(inp, &(shdr->sh_name), nm->is_little, &addr);
	ft_parse_elf_word(inp, &(shdr->sh_type), nm->is_little, &addr);
	ft_parse_shdr_xword(inp, &(shdr->sh_flags), nm, &addr);
	ft_parse_shdr_xword(inp, &(shdr->sh_addr), nm, &addr);
	ft_parse_shdr_xword(inp, &(shdr->sh_offset), nm, &addr);
	ft_parse_shdr_xword(inp, &(shdr->sh_size), nm, &addr);
	ft_parse_elf_word(inp, &(shdr->sh_link), nm->is_little, &addr);
	ft_parse_elf_word(inp, &(shdr->sh_info), nm->is_little, &addr);
	ft_parse_shdr_xword(inp, &(shdr->sh_addralign), nm, &addr);
	ft_parse_shdr_xword(inp, &(shdr->sh_entsize), nm, &addr);
	return (0);
}

static int	ft_validate_elf_shdr(t_nm *nm, Elf64_Shdr *shdr, uint8_t b)
{
	if (shdr->sh_offset > nm->file_size ||
			shdr->sh_offset + shdr->sh_size > nm->file_size)
		return (-1);
	ft_memcpy(nm->shdr_tabs + b, shdr, sizeof(Elf64_Shdr));
	nm->tabs[b] = nm->file + shdr->sh_offset;
	if (b == SHDR_SYM)
		nm->sym_tab_info |= SHDR_SYM_BIT;
	else if (b == SHDR_DYN)
		nm->sym_tab_info |= SHDR_DYN_BIT;
	else if (b == SHDR_SYM_STR)
		nm->sym_tab_info |= SHDR_SYM_STR_BIT;
	else if (b == SHDR_DYN_STR)
		nm->sym_tab_info |= SHDR_DYN_STR_BIT;
	else if (b == SHDR_SSTR)
		nm->sym_tab_info |= SHDR_SSTR_BIT;
	return (0);
}

static int	ft_parse_single_elf_shdr(t_nm *nm, Elf64_Shdr *shdr, uint16_t index)
{
	off_t		offset;
	uint64_t	sh_off;
	uint8_t		b;
	char		*str;

	sh_off = (nm->elf_hdr.e_shoff);
	offset = (index *nm->elf_hdr.e_shentsize);
	ft_extract_single_shdr(nm->file + sh_off + offset, nm, shdr);
	str = (char *)(nm->tabs[SHDR_SSTR] + shdr->sh_name);
	b = 0;
	if (shdr->sh_type == SHT_STRTAB && index == nm->elf_hdr.e_shstrndx)
		b = SHDR_SSTR;
	else if (shdr->sh_type == SHT_STRTAB && !ft_strcmp(str, ".dynstr"))
		b = SHDR_DYN_STR;
	else if (shdr->sh_type == SHT_STRTAB && !ft_strcmp(str, ".strtab"))
		b = SHDR_SYM_STR;
	else if (shdr->sh_type == SHT_SYMTAB)
		b = SHDR_SYM;
	else if (shdr->sh_type == SHT_DYNSYM)
		b = SHDR_DYN;
	else
		return (0);
	return (ft_validate_elf_shdr(nm, shdr, b));
}

int	ft_process_elf_shdr(t_nm *nm)
{
	uint16_t	i;

	if (!nm || !nm->file || !nm->elf_hdr.e_shnum || !nm->shdr)
		return (-1);
	nm->sym_tab_info = 0;
	ft_parse_single_elf_shdr(nm, nm->shdr + nm->elf_hdr.e_shstrndx,
			nm->elf_hdr.e_shstrndx);
	if (!(nm->sym_tab_info & SHDR_SSTR_BIT))
		return (-1);
	i = 0;
	while (i < nm->elf_hdr.e_shnum)
	{
		if (i++ == nm->elf_hdr.e_shstrndx)
			continue ;
		if (ft_parse_single_elf_shdr(nm, nm->shdr + i - 1, i - 1) == -1)
			return (-1);
	}
	if (((nm->sym_tab_info & SHDR_SYM_BIT) && !(nm->sym_tab_info & SHDR_SYM_STR_BIT))
		|| ((nm->sym_tab_info & SHDR_DYN_BIT) && !(nm->sym_tab_info & SHDR_DYN_STR_BIT))
		|| (!(nm->sym_tab_info & SHDR_SYM_BIT) && !(nm->sym_tab_info & SHDR_DYN_BIT)))
		return (-1);
	return (0);
}
