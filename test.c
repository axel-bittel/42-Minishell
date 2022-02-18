#include <stdio.h>
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

int	main()
{
	int	i;

	i = 10;
	char	*chr = ft_strdup("Pute, est Axel");
	char	*chr_ins = ft_strdup("Tommy");
	chr = insert_str(chr, chr_ins, &i, 13);
}
