#ifndef FILLIT_H
# define FILLIT_H

#include "libft.h"
#include <stdio.h> //!!!!!!delete

# define PIECE_SIZE 4


typedef struct		s_lst
{
	char			*shape;
	char			**p_sets;
	int				idx;
	int				curr;
	int				n_sets;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

int		converter_to_bin(char *buf, int *counter);
int		is_same_shape(char *shape, char *moved, int space);
char	*get_shape(char *buf, int space);
char	*ft_move(char *t, char direction, int space);
int		is_error_exist(char *buf);

t_lst	*make_chain_lst(t_lst **head, t_lst **lst, char *buf, int *idx);
char 	**possilbe_sets(t_lst **lst, int space);
int		ft_movable_amount(t_lst **lst, char way, int space);
void	shape_and_sets(t_lst **head, int idx);
void	adjust_shape_by_space(t_lst **t, int space);

void	make_fillit(t_lst **t, int space);
char	*fillit_btracking(char **ans, t_lst **t);
int		is_valid(char **ans, t_lst **t);
char	*detaching_self(char **ans, t_lst **t);

char	*bw_and(char *b1, char *b2);
char	*bw_or(char *b1, char *b2);
char	*bw_xor(char *b1, char *b2);
char	*bw_not(char *b1);
char	*bw_shift_left(char *b1, size_t amount);
char	*bw_shift_right(char *b1, size_t amount);

// char	**holder(char *buf, int idx);

void	return_answer(t_lst **t, int space);


void	pretty_printer(char *shape, int space);
// void	testing_tool(char *shape, char dir);

#endif