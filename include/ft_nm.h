/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:25:18 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/09 16:29:08 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdint.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <elf.h>

# define SHDR_SSTR 0
# define SHDR_SYM_STR 1
# define SHDR_SYM 2
# define SHDR_DYN 3
# define SHDR_DYN_STR 4
# define SHDR_NUM 5

# define SHDR_SSTR_BIT 0x1
# define SHDR_SYM_STR_BIT 0x2
# define SHDR_SYM_BIT 0x4
# define SHDR_DYN_BIT 0x8
# define SHDR_DYN_STR_BIT 0x10

typedef enum e_nm_err_enum
{
	NM_ERR_FILE_NOT_FOUND,
	NM_ERR_NOT_FILE_FRMT
}					t_nm_err_enum;

typedef enum e_nm_sym_type
{
	NM_ST_UNDEF = 0,
	NM_ST_TEXT_SECTION = 1,
	NM_ST_WEAK_SECTION = 2,
	NM_ST_WEAK_OBJ_SECTION = 7,
	NM_ST_RO_DATA_SECTION = 3,
	NM_ST_BSS_SECTION = 4,
	NM_ST_UNDEF_SECTION = 5,
	NM_ST_UNIQUE_SECTION = 8,
	NM_ST_INIT_DATA_SECTION = 6
}					t_nm_sym_type;

typedef struct s_nm
{
	int				fd;
	uint8_t			is_multi_file;
	char			*filename;
	size_t			file_size;
	uint8_t			*file;

	Elf64_Ehdr		elf_hdr;
	uint8_t			elf_class;
	uint8_t			elf_data;
	uint8_t			is_little;

	Elf64_Shdr		*shdr;

	Elf64_Shdr		shdr_tabs[SHDR_NUM];
	uint8_t			*tabs[SHDR_NUM];
	uint8_t			sym_tab_info;

	Elf64_Sym		*syms;
	char			**sym_name;
	size_t			num_syms;

}					t_nm;

void				ft_endian16(uint8_t *addr, uint16_t *out, int is_little);
void				ft_endian32(uint8_t *addr, uint32_t *out, int is_little);
void				ft_endian64(uint8_t *addr, uint64_t *out, int is_little);

void				ft_parse_elf_half(uint8_t *inp, uint16_t *half,
						int is_little, off_t *addr);
void				ft_parse_elf_word(uint8_t *inp, uint32_t *word,
						int is_little, off_t *addr);
void				ft_parse_elf_offset(uint8_t *inp, uint64_t *off,
						t_nm *nm, off_t *addr);
void				ft_parse_shdr_xword(uint8_t *inp, uint64_t *off,
						t_nm *nm, off_t *addr);
off_t				ft_parse_sym_section(uint8_t *inp, uint64_t *off,
						Elf64_Shdr *shdr, t_nm *nm);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putnstr_fd(char *str, size_t n, int fd);
void				ft_putunbr_fd(size_t nbr, int fd);
void				ft_puthex_fd(size_t nbr, uint8_t is_prefix, int fd);
void				ft_print_hex_prefix(size_t nbr, uint8_t is_prefix,
						size_t num_len, int fd);
void				ft_print_spaces(size_t num_len, int fd);
void				ft_putnbr_fd(long nbr, int fd);
int					ft_print_sym_type_caps(t_nm_sym_type se, uint8_t is_caps);

int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_strcmp_case(char *n1, char *n2);
int					ft_strlen(char *s);

void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *d, void *s, size_t n);

void				ft_process_file(char *filename, uint8_t is_multi_file);
int					ft_process_elf_header(t_nm *nm);
int					ft_process_elf_shdr(t_nm *nm);
int					ft_parse_sym_tabs(t_nm *nm);
int					ft_sys_cmp(char *arg1, char *arg2, int *ret);
void				ft_sort_syms(Elf64_Sym *sym, char **sym_name,
						size_t num_syms);
int					ft_process_syms(t_nm *nm);

#endif
