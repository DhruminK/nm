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

/**
static size_t	ft_skip_non_alphanum(char *n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (n[i] && !(n[i] >= 'A' && n[i] <= 'Z')
			&& !(n[i] >= 'a' && n[i] <= 'z')
			&& !(n[i] >= '0' && n[i] <= '9'))
		i += 1;
	return (i);
}

static int	ft_sys_cmp(char *arg1, char *arg2, int *ret)
{
	char	*n1;
	char	*n2;

	if (!arg1 || !arg2 || !ret)
		return (-1);
	n1 = arg1 + ft_skip_non_alphanum(arg1);
	n2 = arg2 + ft_skip_non_alphanum(arg2);
	*ret = ft_strcmp_case(n1, n2);
	if (*ret != 0)
		return (0);
	if (n1 - arg1 > n2 - arg2)
		*ret = -1;
	else if (n1 - arg1 < n2 - arg2)
		*ret = 1;
	return (0);
}
*/

void	ft_sort_syms(Elf64_Sym *syms, char **sym_names, size_t num_syms, t_nm *nm)
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
			if (ft_sys_cmp(sym_names[j], sym_names[j + 1], &ret) == -1)
				return ;
			if (ret > 0)
				ft_sym_swap(syms + j, sym_names + j,
						syms + j + 1, sym_names + j + 1);
			j += 1;
		}
		i += 1;
	}
}
