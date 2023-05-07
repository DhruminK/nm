#include "ft_nm.h"

static int	ft_print_diff_elf_section(Elf64_Shdr *shdr, Elf64_Sym *sym, char *name, t_nm *nm)
{
	char		*s_name;
	uint8_t		st_type;
	uint8_t		st_bind;
	uint32_t	ret;

	if (!shdr || !sym || !name)
		return (-1);
	st_bind = sym->st_info >> 4;
	st_type = sym->st_info & 0xF;
	s_name = nm->tabs[SHDR_SSTR] + (shdr->sh_name);
	ret = !ft_strcmp(s_name, ".text") || !ft_strcmp(s_name, ".fini")
			|| !ft_strcmp(s_name, ".init");
	if (ret)
		return (ft_print_sym_type_caps(NM_ST_TEXT_SECTION, st_bind == STB_GLOBAL));
	if (!ft_strcmp(s_name, ".bss"))
		return (ft_print_sym_type_caps(NM_ST_BSS_SECTION, st_bind == STB_GLOBAL));
	ret = (shdr->sh_flags & SHF_ALLOC) && !(shdr->sh_flags & ~(SHF_ALLOC));
	if (ret)
		return (ft_print_sym_type_caps(NM_ST_RO_DATA_SECTION, st_bind == STB_GLOBAL));
	ret = (shdr->sh_flags & (SHF_WRITE | SHF_ALLOC))
		&& !(shdr->sh_flags & ~(SHF_WRITE | SHF_ALLOC));
	if (ret)
		return (ft_print_sym_type_caps(NM_ST_INIT_DATA_SECTION, st_bind == STB_GLOBAL));
	return (0);
}

static void	ft_print_sym_type(Elf64_Sym *sym, char *name, t_nm *nm)
{
	Elf64_Shdr	*shdr;
	uint8_t		st_type;
	uint8_t		st_bind;
	int			ret;

	if (!sym || !nm || !name)
		return ;
	st_bind = sym->st_info >> 4;
	st_type = sym->st_info & 0xF;
	ret = 0;
	if (st_bind == STB_GNU_UNIQUE)
		ret = ft_print_sym_type_caps(NM_ST_UNIQUE_SECTION,
				sym->st_shndx != SHN_UNDEF);
	if (st_bind == STB_WEAK && st_type == STT_OBJECT)
		ret = ft_print_sym_type_caps(NM_ST_WEAK_OBJ_SECTION,
				sym->st_shndx != SHN_UNDEF);
	if (!ret && st_bind == STB_WEAK)
		ret = (ft_print_sym_type_caps(NM_ST_WEAK_SECTION,
					sym->st_shndx != SHN_UNDEF));
	if (!ret && sym->st_shndx == SHN_UNDEF)
		ret = (ft_print_sym_type_caps(NM_ST_UNDEF_SECTION, 1));
	if (!ret)
		ret = ft_print_diff_elf_section(nm->shdr + sym->st_shndx,
				sym, name, nm);
}

static void	ft_print_single_syms(t_nm *nm, Elf64_Sym *sym, char *sym_name)
{
	size_t	num_len;

	if (!nm || !sym || !sym_name)
		return ;
	num_len = 8;
	if (nm->elf_class == ELFCLASS64)
		num_len = 16;
	if (sym->st_shndx == SHN_UNDEF)
		ft_print_spaces(num_len, 1);
	else
		ft_print_hex_prefix(sym->st_value, 0, num_len, 1);
	ft_putchar_fd(' ', 1);
	ft_print_sym_type(sym, sym_name, nm);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(sym_name, 1);
	ft_putchar_fd('\n', 1);
}

/**
static int	ft_find_dup(t_nm *nm, size_t index)
{
	size_t	len;

	if (!nm)
		return (-1);
	if (index == nm->num_syms - 1)
		return (0);
	len = ft_strlen(nm->sym_name[index]);
	if (ft_strncmp(nm->sym_name[index], nm->sym_name[index + 1], len))
		return (0);
	if (ft_strlen(nm->sym_name[index + 1]) == len)
		return (1);
	if (nm->sym_name[index + 1][len] == '@')
		return (1);
	return (0);
}
*/

int	ft_process_syms(t_nm *nm)
{
	size_t	i;
	uint8_t	st_type;
	uint8_t	st_bind;

	if (!nm || !nm->file || !nm->shdr)
		return (-1);
	ft_sort_syms(nm->syms, nm->sym_name, nm->num_syms, nm);
	if (nm->is_multi_file)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(nm->filename, 1);
		ft_putstr_fd(":\n", 1);
	}
	i = 0;
	while (i < nm->num_syms)
	{
		st_bind = nm->syms[i].st_info >> 4;
		st_type = nm->syms[i].st_info & 0xF;
		if (st_type != STT_FILE && nm->sym_name[i][0])// && ft_find_dup(nm, i) < 1)
			ft_print_single_syms(nm, nm->syms + i, nm->sym_name[i]);
		i += 1;
	}
	return (0);
}
