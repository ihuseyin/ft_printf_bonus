#include "ft_printf_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (start);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	while (len--)
	{
		*ptr++ = (unsigned char)c;
	}
	return (dest);
}
