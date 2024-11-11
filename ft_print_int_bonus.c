#include "ft_printf_bonus.h"

static size_t	ft_count(long n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa(long n, char *sign)
{
	char	*str;
	int		len;

	len = ft_count(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	else if (n < 0)
	{
		*sign = '-';
		n = -n;
	}
	while (n != 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static int	ft_write_int(char *s, t_flags *flags, char *sign, t_format format)
{
	int	count;

	count = 0;
	if (flags->minus)
	{
		if (*sign != '\0')
			count += write(1, sign, 1);
		while (format.precision-- > 0)
			count += write(1, "0", 1);
		count += write(1, s, format.number_len);
	}
	while (format.width-- > 0)
		count += write(1, " ", 1);
	if (!flags->minus)
	{
		if (*sign != '\0')
			count += write(1, sign, 1);
		while (format.precision-- > 0)
			count += write(1, "0", 1);
		count += write(1, s, format.number_len);
	}
	return (count);
}

static int	ft_parse_for_int(char *s, t_flags *flags, char *sign)
{
	int			count;
	t_format	fmt;

	count = 0;
	if (*s == '0' && flags->precision == -1)
		*s = '\0';
	fmt.number_len = ft_strlen(s);
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
	count = ft_write_int(s, flags, sign, fmt);
	return (count);
}

int	ft_print_int(long n, t_flags *flags, int is_unsigned)
{
	int		count;
	char	*str;
	char	sign;

	sign = '\0';
	count = 0;
	if (is_unsigned)
		str = ft_itoa(n, &sign);
	else
	{
		if (flags->plus && n >= 0)
			sign = '+';
		else if (flags->space && n >= 0)
			sign = ' ';
		str = ft_itoa(n, &sign);
	}
	count += ft_parse_for_int(str, flags, &sign);
	free(str);
	return (count);
}
