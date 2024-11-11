#include "ft_printf_bonus.h"

int	ft_print_ptr(void *ptr, t_flags *flags)
{
	int				count;
	unsigned long	address;

	count = 0;
	address = (unsigned long)ptr;
	flags->hash = 1;
	count += ft_print_hex(address, flags, 'p');
	return (count);
}
