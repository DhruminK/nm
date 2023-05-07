#include "ft_nm.h"

static void	ft_print_err(t_nm_err_enum err, char *filename)
{
	ft_putstr_fd("ft_nm: ", 2);
	if (err == NM_ERR_FILE_NOT_FOUND)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("': No such file\n", 2);
	}
	else if (err == NM_ERR_NOT_FILE_FRMT)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": file format not recognized\n", 2);
	}
}

static int	ft_open_file(char *filename, t_nm *nm)
{
	struct stat	statbuf;

	if (!filename || !nm)
		return (-1);
	ft_memset(nm, 0, sizeof(t_nm));
	ft_memset(&statbuf, 0, sizeof(struct stat));
	nm->filename = filename;
	nm->fd = open(filename, O_RDONLY);
	if (nm->fd < 0)
		return (-1);
	if (fstat(nm->fd, &statbuf) == -1)
		return (-1);
	nm->file_size = statbuf.st_size;
	nm->file = mmap(0, nm->file_size, PROT_READ, MAP_PRIVATE, nm->fd, 0);
	if (nm->file == MAP_FAILED)
		return (-2);
	return (0);
}

static void	ft_free_nm(t_nm *nm)
{
	if (nm->fd > -1)
		close(nm->fd);
	nm->filename = 0;
	if (nm->shdr)
		free(nm->shdr);
	if (nm->syms)
		free(nm->syms);
	if (nm->file)
		munmap(nm->file, nm->file_size);
	ft_memset(nm, 0, sizeof(t_nm));
}

void	ft_process_file(char *filename, uint8_t is_multi_file)
{
	t_nm	nm;
	int		ret;

	if (!filename)
		return ;
	if (ft_open_file(filename, &nm) == -1)
		return (ft_print_err(NM_ERR_FILE_NOT_FOUND, filename));
	nm.is_multi_file = is_multi_file;
	ret = ft_process_elf_header(&nm);
	if (ret > -1)
		ret = ft_process_elf_shdr(&nm);
	if (ret > -1)
		ret = ft_parse_sym_tabs(&nm);
	if (ret > -1)
		ret = ft_process_syms(&nm);
	ft_free_nm(&nm);
	if (ret == -2)
		return (ft_print_err(NM_ERR_FILE_NOT_FOUND, filename));
	else if (ret == -1)
		return (ft_print_err(NM_ERR_NOT_FILE_FRMT, filename));
}
