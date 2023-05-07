#include "ft_nm.h"

static int	ft_parse_elf_magic(uint8_t *addr, t_nm *nm)
{
	if (!addr || !nm)
		return (-1);
	if (!(addr[EI_MAG0] == ELFMAG0 && addr[EI_MAG1] == ELFMAG1
			&& addr[EI_MAG2] == ELFMAG2 && addr[EI_MAG3] == ELFMAG3))
		return (0);
	nm->elf_class = addr[EI_CLASS];
	if (nm->elf_class == ELFCLASSNONE || nm->elf_class >= ELFCLASSNUM)
		return (0);
	nm->elf_data = addr[EI_DATA];
	if (nm->elf_data == ELFDATANONE || nm->elf_data >= ELFDATANUM)
		return (0);
	nm->is_little = nm->elf_data == ELFDATA2LSB;
	if (addr[EI_VERSION] != EV_CURRENT)
		return (0);
	return (1);
}

static int	ft_parse_elf_ext_header(uint8_t *inp, t_nm *nm)
{
	off_t	addr;

	if (!inp || !nm)
		return (-1);
	addr = 0;
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_type), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_machine), nm->is_little, &addr);
	ft_parse_elf_word(inp, &(nm->elf_hdr.e_version), nm->is_little, &addr);
	ft_parse_elf_offset(inp, &(nm->elf_hdr.e_entry), nm, &addr);
	ft_parse_elf_offset(inp, &(nm->elf_hdr.e_phoff), nm, &addr);
	ft_parse_elf_offset(inp, &(nm->elf_hdr.e_shoff), nm, &addr);
	ft_parse_elf_word(inp, &(nm->elf_hdr.e_flags), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_ehsize), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_phentsize), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_phnum), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_shentsize), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_shnum), nm->is_little, &addr);
	ft_parse_elf_half(inp, &(nm->elf_hdr.e_shstrndx), nm->is_little, &addr);
	return (1);
}

int	ft_process_elf_header(t_nm *nm)
{
	int	ret;

	if (!nm || !(nm->file))
		return (-2);
	ret = ft_parse_elf_magic(nm->file, nm);
	if (ret < 1)
		return (ret - 1);
	ft_parse_elf_ext_header(nm->file + EI_NIDENT, nm);
	if (nm->elf_hdr.e_shoff > nm->file_size ||
			nm->elf_hdr.e_shoff
			+ (nm->elf_hdr.e_shentsize * nm->elf_hdr.e_shnum) > nm->file_size)
		return (-1);
	nm->shdr = malloc(nm->elf_hdr.e_shnum * sizeof(Elf64_Shdr));
	ft_memset(nm->shdr, 0, sizeof(Elf64_Shdr));
	return (0);
}
