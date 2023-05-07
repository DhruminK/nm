#include "ft_nm.h"

void	ft_endian16(uint8_t *addr, uint16_t *out, int is_little)
{
	if (!addr || !out)
		return ;
	if (is_little)
		out[0] = (addr[1] << 8) | addr[0];
	else
		out[0] = (addr[0] << 8) | addr[1];
}

void	ft_endian32(uint8_t *addr, uint32_t *out, int is_little)
{
	if (!addr || !out)
		return ;
	if (is_little)
		out[0] = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	else
		out[0] = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3];
}

void	ft_endian64(uint8_t *addr, uint64_t *out, int is_little)
{
	int	i;
	int	dir;

	if (!addr || !out)
		return ;
	i = 0;
	dir = 1;
	if (is_little)
	{
		i = 7;
		dir = -1;
	}
	out[0] = 0;
	while (i >= 0 && i < 8)
	{
		out[0] = (out[0] << 8) | (addr[i]);
		i += dir;
	}
}
