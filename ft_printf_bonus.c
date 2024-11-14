#include "ft_printf_bonus.h"

static void	ft_parse_width_and_precision(const char **format, t_flags *flags)
{
	int	width;
	int	precision;

	width = 0;
	if (**format >= '1' && **format <= '9')
	{
		while (**format >= '0' && **format <= '9')
		{
			width = width * 10 + (*(*format)++ - '0');
		}
		flags->width = width;
	}
	if (**format == '.')
	{
		precision = 0;
		(*format)++;
		while (**format >= '0' && **format <= '9')
		{
			precision = precision * 10 + (**format - '0');
			(*format)++;
		}
		flags->precision = precision;
		if (!precision)
			flags->precision = -1;
	}
}

static void	ft_parse_flags(const char **format, t_flags *flags)
{
	while (**format == '-' || **format == '0' || **format == '#'
		|| **format == ' ' || **format == '+')
	{
		if (**format == '-')
			flags->minus = 1;
		else if (**format == '0')
			flags->zero = 1;
		else if (**format == '#')
			flags->hash = 1;
		else if (**format == ' ')
			flags->space = 1;
		else if (**format == '+')
			flags->plus = 1;
		(*format)++;
	}
}

static int	ft_print_format(char specifier, va_list ap, t_flags *flags)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = ft_print_char(va_arg(ap, int), flags);
	else if (specifier == 's')
		count = ft_print_str(va_arg(ap, char *), flags);
	else if (specifier == 'p')
		count = ft_print_ptr(va_arg(ap, void *), flags);
	else if (specifier == 'd' || specifier == 'i')
		count = ft_print_int(va_arg(ap, int), flags, 0);
	else if (specifier == 'u')
		count = ft_print_int(va_arg(ap, unsigned int), flags, 1);
	else if (specifier == 'x' || specifier == 'X')
		count = ft_print_hex((unsigned int)va_arg(ap, unsigned long),
				flags, specifier);
	else if (specifier == '%')
		count = write(1, "%", 1);
	else
	{
		count += write(1, "%", 1);
		count += write(1, &specifier, 1);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	t_flags	flags;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			ft_memset(&flags, 0, sizeof(t_flags));
			format++;
			ft_parse_flags(&format, &flags);
			ft_parse_width_and_precision(&format, &flags);
			count += ft_print_format(*format, ap, &flags);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
