#include "fillit.h"

#include <stdio.h>




int main(int argc, char *argv[])
{
	int		i;
	int		fd;
	int		counter;
	char	*temp;
	char	buf[17];
	char 	sets[4][17];

	i = 1;
	counter = 0;
	temp = NULL;
	if (argc < 2)
		return 0;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		while (get_next_line(fd, &temp) > 0)
		{
			counter += ft_strcmp(temp, "\0") != 0 ? 4 : 0;
			ft_strcat(buf, temp);
			if (counter == 16)
			{
				buf[16] = '\0';
				converter(buf, fd, &counter);
				// fillit(buf);
			}
			ft_strdel(&temp);
		}
		i++;
	}
	while(i < 2)
		printf("%s\n", sets[i++]);
	return (0);
}