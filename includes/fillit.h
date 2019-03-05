#ifndef FILLIT_H
# define FILLIT_H

#include "libft.h"
#include <stdio.h> //!!!!!!delete

typedef struct		s_lst
{
	char			*shape;
	char			**p_sets;
	int				idx;
	int				curr;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

void	converter(char *buf, int *counter);
int		is_same_shape(char *shape, char *moved);
char	*get_shape(char *buf);
char	*ft_move(char *t, char direction);

t_lst	*make_chain_lst(t_lst **head, t_lst **lst, char *buf, int *idx);
char 	**possilbe_sets(t_lst **lst);
int		ft_movable_amount(t_lst **lst, char way);

void	fillit(t_lst **head);

// char	**holder(char *buf, int idx);




void	pretty_printer(char *shape);
void	testing_tool(char *shape, char dir);

#endif