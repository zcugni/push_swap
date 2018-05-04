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
    ft_putstr("Error\n");
    return(0);
}

#include <stdio.h>

int     valid_input(int argc, char **argv, t_tab_inf *tab_inf, t_list **lst_a, t_param *param)
{
    int i;
    int tmp_nb;
    int already_sorted;

    already_sorted = 1;
    if (argc > 1)
    {
        //recupere les params
        if (ft_strcmp(argv[1], "-v") == 0 || (argv[2] && ft_strcmp(argv[2], "-v") == 0))
            param->verbose = 1;
        else
            param->verbose = 0;
        if (ft_strcmp(argv[1], "-c") == 0 || (argv[2] && ft_strcmp(argv[2], "-c") == 0))
            param->color = 1;
        else
            param->color = 0;
        i = param->verbose + param->color + 1;
        if (argc <= i)
            return (0);
        tab_inf->sorted = malloc((argc - i) * sizeof(int));
        while (argv[i])
        {
            if(is_int(argv[i]))
            {
                tmp_nb = ft_atoi(argv[i]);
                if (tmp_nb < tab_inf->sorted[i - param->color - param->verbose - 2])
                    already_sorted = 0;
                tab_inf->sorted[i - param->color - param->verbose - 1] = tmp_nb;
                ft_lstappend(lst_a, ft_lstnew(&tmp_nb, sizeof(tmp_nb)));
            }
            else
                return (0);
            i++;
        }
        tab_inf->sorted_len = i - 1 - param->color - param->verbose;
        if (!already_sorted)
            return (quicksort(tab_inf->sorted, tab_inf->sorted_len));
    }
    else
        return (0);
    return (1);
    //rien faire si c'est deja trié
}