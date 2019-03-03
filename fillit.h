#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"
#include <stdio.h> //!!!!!!delete

char	*converter( char *buf, int fd, int *counter);
void	fillit(char *buf);
int		get_start_idx(char *str);
char	*make_base(char *base, int str_base);
int		ft_atoi_base(const char *str, int str_base);
int		ft_stridx(char *str, char c);
// char    **holder(char *buf, int idx);


#endif