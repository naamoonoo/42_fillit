#ifndef FILLIT_H
# define FILLIT_H

#include "libft.h"
#include <stdio.h> //!!!!!!delete

# define PIECE_SIZE 4
# define ERROR -1
# define SUCCESS 0
# define YES 1
# define NO 0
# define MIN_SQUARE "AA\nAA"


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


/* 
** -------------------read & validation-------------------
*/

int		reading_tetrimono(int fd, t_lst **head, int *idx);
int		converter(char *buf, int *count);
int		is_valid_shape(char *shape);
char	*get_shape_vert(char *shape, int space);
char	*get_shape_hori(char *shape, int space);

/* 
** -------------------double linked lst handle-------------------
*/

t_lst	*make_chain_lst(t_lst **head, t_lst **lst, char *buf, int *idx);
int		shape_and_sets(t_lst **head, int space);
char 	**possilbe_sets(t_lst **lst, int space);
int		mov_amount(t_lst **lst, char way, int space);

/* 
** -------------------tetrimono handle-------------------
*/

int		is_same_shape(char *shape, char *moved, int space);
char	*ft_move(char *t, char direction, int space);
void	adjust_shape_by_space(t_lst **t, int space);

/* 
** -------------------fillit algirithm-------------------
*/

void	make_fillit(t_lst **t, int space);
char	*fillit_btracking(char **ans, t_lst **t);
char	*go_to_prev(char **ans, t_lst **t);
int		is_valid_set(char **ans, t_lst **t);
char	*detaching_self(char **ans, t_lst **t);

/* 
** -------------------bitwise copying-------------------
*/

char	*bw_and(char *b1, char *b2);
char	*bw_or(char *b1, char *b2);
char	*bw_xor(char *b1, char *b2);
char	*bw_not(char *b1);
char	*bw_shift_left(char *b1, size_t amount);
char	*bw_shift_right(char *b1, size_t amount);

/* 
** -------------------result print-------------------
*/

void	print_answer(t_lst **t, int space);
int		print_error(void);

void	pretty_printer(char *shape, int space);
// void	testing_tool(char *shape, char dir);

#endif