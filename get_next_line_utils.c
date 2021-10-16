#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	temp = malloc(count * size);
	if (!temp)
		return (temp);
	ft_bzero(temp, size * count);
	return (temp);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return ((char *)(s + i));
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*temp;
	int		l1;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	i = 0;
	temp = malloc(l1 + ft_strlen(s2) + 1);
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		temp[l1 + i] = s2[i];
		i++;
	}
	temp[l1 + i] = 0;
	return (temp);
}

static char	*ft_mystrlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	strlen;

	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (len >= strlen)
		len = strlen;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	if (start > strlen)
	{
		result[0] = '\0';
		return (result);
	}	
	result = ft_mystrlcpy(result, &s[start], len);
	return (result);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)malloc(1 + sizeof(char) * ft_strlen(s1));
	if (!s)
		return (s);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = 0;
	return (s);
}
