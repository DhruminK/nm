#include "ft_nm.h"

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 2)
		av[i--] = "a.out";
	if (ac == 1 || ac == 2)
	{
		ft_process_file(av[ac - 1], 0);
		return (0);
	}
	while (++i < ac)
	{
		ft_process_file(av[i], 1);
	}
	return (0);
}
