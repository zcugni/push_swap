#include "push_swap.h"

static int     is_int(char *str)
{
    int i;
    int is_neg;

    if (ft_isdigit(str[0]))
        is_neg = 0;
    else if (str[0] == '-')
        is_neg = 1;
    else
        return (0);

    i = 1;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    if (i < 10 - is_neg)
        return (1);
    else
        return (0);
    //si on a 9 chiffres je devrais verifier si on rest inferieur au int max
        //mais c'est chiant alors osef...
}

int    display_error()
{
    //ca doit etre sur la sortie d'erreur
    ft_putstr("Error\n");
    return(0);
}

static int    read_file(int fd, t_tab_inf *tab_inf, t_list **lst_a)
{
    char    **arg;
    int     i;
	t_list	*tmp_lst;
	int		tmp_nb;

    arg = malloc(sizeof(char *));
    i = 0;
    while (get_next_line(fd, arg, ' ')) //je verifie pas si le read vaut -1 en occurrence
    {
        if(is_int(*arg))
        {
            tmp_nb = ft_atoi(*arg);
            ft_lstappend(lst_a, ft_lstnew(&tmp_nb, sizeof(tmp_nb)));
        }
        else
            return (0);
        i++;
	}
	tab_inf->sorted = malloc(i * sizeof(int));
	tab_inf->sorted_len = i;
	i = 0;
	tmp_lst = *lst_a;
	while (i < tab_inf->sorted_len)
	{
		tab_inf->sorted[i] = *((int *)tmp_lst->content);
		i++;
		tmp_lst = tmp_lst->next;
		//if (tmp_nb < tab_inf->sorted[i - param->color - param->verbose - 2])
        //    already_sorted = 0;
	}
	//if (!already_sorted)
    return (quicksort(tab_inf->sorted, tab_inf->sorted_len));
}
static int	read_args(char **argv, t_tab_inf *tab_inf, t_list **lst_a)
{
	int i;
	int tmp_nb;

	i = 0;
	tab_inf->sorted = malloc(tab_inf->sorted_len * sizeof(int));
    while (argv[i])
    {
    	if(is_int(argv[i]))
        {
            tmp_nb = ft_atoi(argv[i]);
            //if (tmp_nb < tab_inf->sorted[i - param->color - param->verbose - 2])
             //   already_sorted = 0;
            tab_inf->sorted[i] = tmp_nb;
            ft_lstappend(lst_a, ft_lstnew(&tmp_nb, sizeof(tmp_nb)));
        }
        else
            return (0);
        i++;
    }
    //if (!already_sorted)
        return (quicksort(tab_inf->sorted, tab_inf->sorted_len));
}

int     valid_input(int argc, char **argv, t_tab_inf *tab_inf, t_list **lst_a, t_param *param)
{
    int i;
    //int already_sorted;
    int fd;

    //already_sorted = 1;
    if (argc > 1)
    {
        //param->silent = 1; //a enlever;
        param->silent = 0; //a enlever;
        if (ft_strcmp(argv[1], "-v") == 0 || (argv[2] && ft_strcmp(argv[2], "-v") == 0))
            param->verbose = 1;
        else
            param->verbose = 0;
        if (ft_strcmp(argv[1], "-c") == 0 || (argv[2] && ft_strcmp(argv[2], "-c") == 0))
            param->color = 1;
        else
            param->color = 0;
        if (ft_strcmp(argv[1], "-f") == 0 || (argv[2] && ft_strcmp(argv[2], "-f") == 0))
            param->full = 1;
        else
            param->full = 0;
        i = param->verbose + param->color + 1;
        if (argc <= i)
            return (0);
        fd = open(argv[i], O_RDONLY);
        if (!is_int(argv[i]) && fd == -1)
            return (0);
        else if (!is_int(argv[i]))
			return (read_file(fd, tab_inf, lst_a));
        else
		{
			tab_inf->sorted_len = argc - i;
			return (read_args(&(argv[i]), tab_inf, lst_a));
		}
    }
    else
        return (0);
    //rien faire si c'est deja trié
}