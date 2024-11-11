#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_format
{
	int	precision;
	int	width;
	int	number_len;
}		t_format;

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	hash;
	int	space;
	int	plus;
	int	width;
	int	precision;
}	t_flags;

int	ft_print_char(int c, t_flags *flags);
int	ft_print_str(char *s, t_flags *flags);
int	ft_print_int(long n, t_flags *flags, int is_unsigned);
int	ft_print_hex(unsigned long n, t_flags *flags, char specifier);
int	ft_print_ptr(void *ptr, t_flags *flags);
int	ft_printf(const char *format, ...);

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int	ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *dest, int c, size_t len);

#endif
