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

int     valid_input(int argc, char **argv, int **sorted, int *sorted_len, t_lst_inf *lst_inf, int *verbose, int *color)
{
    int i;
    int tmp_nb;
    int already_sorted;

    already_sorted = 1;
    if (argc > 1)
    {
        //recupere les params
        if (ft_strcmp(argv[1], "-v") == 0 || (argv[2] && ft_strcmp(argv[2], "-v") == 0))
            *verbose = 1;
        else
            *verbose = 0;
        if (ft_strcmp(argv[1], "-c") == 0 || (argv[2] && ft_strcmp(argv[2], "-c") == 0))
            *color = 1;
        else
            *color = 0;
        i = *verbose + *color + 1;
        if (argc <= i)
            return (0);
        *sorted = malloc((argc - i) * sizeof(int));
        while (argv[i])
        {
            if(is_int(argv[i]))
            {
                tmp_nb = ft_atoi(argv[i]);
                if (tmp_nb < (*sorted)[i - *color - *verbose - 2])
                    already_sorted = 0;
                (*sorted)[i - *color - *verbose - 1] = tmp_nb;
                ft_lstappend(&(lst_inf->lst_a), ft_lstnew(&tmp_nb, sizeof(tmp_nb)));
            }
            else
                return (0);
            i++;
        }
        *sorted_len = i - 1 - *color - *verbose;
        if (!already_sorted)
            return (quicksort(*sorted, *sorted_len));
    }
    else
        return (0);
    return (1);
    //rien faire si c'est deja trié
}