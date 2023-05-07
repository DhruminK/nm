#include "ft_nm.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*src;
	size_t	i;

	src = (char *)s;
	i = 0;
	while (i < n)
	{
		src[i] = (char)(c & 0xFF);
		i += 1;
	}
	return (s);
}

void	*ft_memcpy(void *d, void *s, size_t n)
{
	char	*dst;
	char	*src;
	size_t	i;

	dst = (char *)d;
	src = (char *)s;
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i += 1;
	}
	return (d);
}

int	ft_strcmp(char *s1, char *s2)
{
	long	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (-(s2[0]));
	if (s1 && !s2)
		return (s1[0]);
	while (s1[0] && s2[0])
	{
		i = s1[0] - s2[0];
		if (i != 0)
			return (i);
		s1 += 1;
		s2 += 1;
	}
	return (s1[0] - s2[0]);
}
