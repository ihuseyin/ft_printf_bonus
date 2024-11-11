#include "ft_printf_bonus.h"

static int	ft_write_str(char *s, t_flags *flags, int len)
{
	int	count;
	int	width;

	count = 0;
	width = flags->width - len;
	if (flags->minus)
		count += write(1, s, len);
	while (width-- > 0)
		count += write(1, " ", 1);
	if (!flags->minus)
		count += write(1, s, len);
	return (count);
}

int	ft_print_str(char *s, t_flags *flags)
{
	char	*pre_str;
	int		count;
	int		len;

	count = 0;
	if (s == NULL)
		s = "(null)";
	pre_str = s;
	if (flags->precision > 0 || flags->precision == -1)
	{
		if (!ft_strcmp(s, "(null)") && flags->precision < 6)
			len = 0;
		else
		{
			while (*pre_str && flags->precision-- > 0)
				pre_str++;
			len = pre_str - s;
		}
	}
	else
		len = ft_strlen(s);
	count = ft_write_str(s, flags, len);
	return (count);
}
