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
	{
		arg1 += ft_skip_non_alphanum(arg1, num_skip);
		arg2 += ft_skip_non_alphanum(arg2, num_skip + 1);
		*ret = ft_char_cmp(*arg1, *arg2);
		if (*ret)
			break ;
		arg1 += 1;
		arg2 += 1;
	}
	if (!*ret && (!*arg1 && *arg2) || (*arg1 && !*arg2))
		*ret = (*arg1 - *arg2);
	if (*ret)
		return (0);
	if (num_skip[0] > num_skip[1])
		*ret = -1;
	else if (num_skip[0] < num_skip[1])
		*ret = 1;
	return (0);
}
