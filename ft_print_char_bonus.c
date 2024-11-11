#include "ft_printf_bonus.h"

int	ft_print_char(int c, t_flags *flags)
{
	int	count;
	int	width;

	count = 0;
	width = flags->width;
	if (flags->minus)
		count += write(1, &c, 1);
	while (--width > 0)
		count += write(1, " ", 1);
	if (!flags->minus)
		count += write(1, &c, 1);
	return (count);
}
