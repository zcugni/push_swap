#include "push_swap.h"

int				init_param_ps(int argc, char **argv, t_param *param, int *first_nb)
{
	int i;

	i = 1;
	param->verbose = 0;
	param->all = 0;
	param->file = 0;
	param->silent = 0;
	param->color = 0;
	while (argv[i] && argv[i][0] == '-' && ft_isalpha(argv[i][1]))
	{
		if (ft_strcmp(argv[i], "-v") == 0)
			param->verbose = 1;
		if (ft_strcmp(argv[i], "-c") == 0)
			param->color = 1;
		if (ft_strcmp(argv[i], "-a") == 0)
			param->all = 1;
        if (ft_strcmp(argv[i], "-f") == 0)
			param->file = 1;
		i++;
	}
	i = param->verbose + param->color + param->full + 1;
	*first_nb = i;
	if (argc <= i)
		return (0);
	return (1);
	//rajouter un usage
	//rajouter help
}

int				init_param_ch(int argc, char **argv, t_param *param, int *first_nb)
{
	int i;

	i = 1;
	param->verbose = 0;
	param->all = 0;
	param->file = 0;
	param->silent = 0;
	param->color = 0;
	while (argv[i] && argv[i][0] == '-' && ft_isalpha(argv[i][1]))
	{
		if (ft_strcmp(argv[i], "-v") == 0)
			param->verbose = 1;
		if (ft_strcmp(argv[i], "-c") == 0)
			param->color = 1;
		if (ft_strcmp(argv[i], "-f") == 0)
			param->full = 1;
		i++;
	}
	i = param->verbose + param->color + param->full + 1;
	*first_nb = i;
	if (argc <= i)
		return (0);
	return (1);
	//rajouter un usage
	//rajouter help
}