#ifndef GET_NEXT_LINE_H
# define  GET_NEXT_LINE_H

#include    <unistd.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>  

size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
#endif