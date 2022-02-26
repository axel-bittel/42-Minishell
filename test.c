#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

char	*insert_str(char *str, char *str_ins, int *deb, int end)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = -1;
	j = -1;
	k = end;
	res = malloc (sizeof(char) * (ft_strlen(str_ins) + ft_strlen(str) - (*deb - end + 1) + 1));
	while (++i < *deb)
		res[i] = str[i];
	while (++j < (int)ft_strlen(str_ins))
		res[i + j] = str_ins[j];
	while (str[++k])
		res[i + j++] = str[k];
	free(str);
	free(str_ins);
	*deb += ft_strlen(str_ins);
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	old;
	int	fd;

	envp[0] = "bite=test=nonouiouiouio";
	fd = open("res", O_WRONLY | O_APPEND);
	old = dup(1);
	dup2(fd, 1);
	write(fd, "test\n", 5);
	dup2(old, 1);
	write(1, "test2\n", 6);
}
