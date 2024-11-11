#include "ft_printf_bonus.h"

static void	ft_parse_hex(unsigned long n, char *hex, char specifier)
{
	int		i;
	int		j;
	char	*symbols;
	char	reverse_hex[16];

	i = 0;
	j = 0;
	if (specifier == 'X')
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (n == 0)
	{
		hex[0] = '0';
		j++;
	}
	while (n > 0)
	{
		reverse_hex[i++] = symbols[n % 16];
		n /= 16;
	}
	while (--i >= 0)
		hex[j++] = reverse_hex[i];
	hex[j] = '\0';
}

static int	ft_write_hex(char *hex, t_flags *flags, char *sign, t_format format)
{
	int	count;

	count = 0;
	if (flags->minus)
	{
		if (*sign != '\0')
			count += write(1, sign, ft_strlen(sign));
		while (format.precision-- > 0)
			count += write(1, "0", 1);
		count += write(1, hex, format.number_len);
	}
	while (format.width-- > 0)
		count += write(1, " ", 1);
	if (!flags->minus)
	{
		if (*sign != '\0')
			count += write(1, sign, ft_strlen(sign));
		while (format.precision-- > 0)
			count += write(1, "0", 1);
		count += write(1, hex, format.number_len);
	}
	return (count);
}

static int	ft_parse_for_hex(char *hex, t_flags *flags, char *sign, int num_len)
{
	int			count;
	t_format	fmt;

	fmt.number_len = num_len;
	count = 0;
	if (flags->precision > fmt.number_len)
		fmt.precision = flags->precision - fmt.number_len;
	else
		fmt.precision = 0;
	fmt.width = flags->width - ft_strlen(sign) - fmt.precision - fmt.number_len;
	if (!flags->precision && fmt.width > 0 && flags->zero && !flags->minus)
	{
		fmt.precision = fmt.width;
		fmt.width = 0;
	}
	count = ft_write_hex(hex, flags, sign, fmt);
	return (count);
}

static void	ft_for_ptr(unsigned long n, char *hex, char *sign, t_flags *flags)
{
	if (n == 0)
	{
		ft_strcpy(hex, "(nil)");
	}
	else if (flags->plus)
	{
		ft_strcpy(sign, "+0x");
	}
	else if (flags->space)
	{
		ft_strcpy(sign, " 0x");
	}
	else
	{
		ft_strcpy(sign, "0x");
	}
	flags->hash = 0;
}

int	ft_print_hex(unsigned long n, t_flags *flags, char specifier)
{
	int		count;
	int		len;
	char	hex[16];
	char	sign[4];

	count = 0;
	if (n == 0 && flags->precision == -1)
		hex[0] = '\0';
	else
		ft_parse_hex(n, hex, specifier);
	sign[0] = '\0';
	if (specifier == 'p')
		ft_for_ptr(n, hex, sign, flags);
	len = ft_strlen(hex);
	if (flags->hash && n > 0)
	{
		sign[0] = '0';
		sign[1] = specifier;
		sign[2] = '\0';
	}
	count += ft_parse_for_hex(hex, flags, sign, len);
	return (count);
}
