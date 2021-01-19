#include "get_next_line.h"
# include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		main(void)
{
	char	*line;
	int		i;

	i = 1;
	while (i == 1)
	{
		i = get_next_line(&line);
		printf("OUTPUT OF GNL: %d | %s\n", i, line);
		free(line);
	}
	// on a mac: 
	// use:
	//leaks [program name]
	// to check for leaks while the program is running
	// you can comment this out if you just want it to run through it
	//while (1) {;}

	return (0);
}
