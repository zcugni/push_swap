#include "push_swap.h"

int get_int(t_lst_inf *lst_inf, char lst_letter)
{
    if (lst_letter == 'a')
        return (*((int *)lst_inf->lst_a->content));
    else
        return (*((int *)lst_inf->lst_b->content));
}

int get_desired(t_tab_inf *tab_inf)
{
    return (tab_inf->sorted[tab_inf->next_index]);
}