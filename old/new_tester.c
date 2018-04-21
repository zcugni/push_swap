#include "stdio.h"
#include "push_swap.h"
#include "new_lst.c" //a ameliorer

int min = 0;
t_g_list *analysis = NULL;
t_path_dist *current_path = NULL;

int     is_sorted(t_list *lst)
{
    t_list *tmp;
    int     sorted;

    tmp = lst;
    sorted = 1;
    while (sorted && tmp)
    {
        if (tmp->next)
            if (tmp->nb > tmp->next->nb)
                sorted = 0;
        tmp = tmp->next;
    }
    return (sorted);
}

void    do_new(t_list **nb_instruct_lst, int *sorted, t_list **lst_a_ori, t_list **lst_b, int len_ori, char *past_instruct, int *nb_instruct)
{
    int res;
    int len;

    res = 1;
    len = len_ori;
    while (res)
	{
        if (*nb_instruct > min && min != 0)
        {
            res = 0;
            printf("stop %i\n", min);
        }
        else
        {
            res = define_instruct(sorted, lst_a_ori, NULL, lst_b, &len, len_ori, 1, &past_instruct, nb_instruct, 0);
        }

        /*res = define_instruct(sorted, lst_a_ori, NULL, lst_b, &len, len_ori, 1, &past_instruct, nb_instruct, 0);
		printf("\n");
        if (*nb_instruct > min && min != 0)
        {
            res = 0;
            printf("stop\n");
        }*/
	}
    if ((*nb_instruct > min && min != 0))
    {
        ft_lstappend(nb_instruct_lst, ft_lstnew(100));
        *nb_instruct = 100;
    }
    else
        ft_lstappend(nb_instruct_lst, ft_lstnew(*nb_instruct));
        

    if (*nb_instruct == 100 || (is_sorted(*lst_a_ori) && !(*lst_b)))
    {
        //ajout dans analysis
        //proteger les mallocs
        t_g_list *new_analysis = malloc(sizeof(t_g_list));
        new_analysis->next = NULL;
        new_analysis->content = malloc(sizeof(t_path_dist));

        ((t_path_dist *)new_analysis->content)->instruct = ft_g_lstcpy(current_path->instruct);
        ((t_path_dist *)new_analysis->content)->dist = *nb_instruct;
        ((t_path_dist *)new_analysis->content)->state = NULL;

        t_g_list *first_current_state = current_path->state;
        while (current_path->state)
        {
            t_g_list *new_state_content = ft_list_lstnew(ft_lstcpy(current_path->state->content), sizeof(t_list *));
            ft_g_lstappend(&(((t_path_dist *)new_analysis->content)->state), new_state_content);
            current_path->state = current_path->state->next;
        }
        current_path->state = first_current_state;
        ft_g_lstappend(&analysis, new_analysis);
        if (*nb_instruct != 100)
        {
            printf("\033[31myip %i\n\033[0m", min);
            if (min == 0 || min > *nb_instruct)
            {
                printf("yop\n");
                min = *nb_instruct;
            }
        }
    }

    //remise a 0
    if (current_path->instruct->next)
    {
        t_g_list *tmp_current = current_path->instruct;
        while (tmp_current->next->next)
            tmp_current = tmp_current->next;
        free(tmp_current->next->content);
        free(tmp_current->next);
        tmp_current->next = NULL;

        t_g_list *last_state = current_path->state;
        while (last_state->next->next)
            last_state = last_state->next;
        t_list *please = last_state->next->content;
        lst_clr(&please);
        free(last_state->next);
        last_state->next = NULL;
    }
    else
    {
        free(current_path->instruct->content);
        free(current_path->instruct);
        t_list *please = current_path->state->content;
        lst_clr(&please);
        free(current_path->state);
        free(current_path);
        current_path = NULL;
    }

    //clear of new analysis, necessary or not ? (faire gaffe, avec ma condition analysis existe pas toujours)
    /*t_g_list *tmp_state_clr = ((t_path_dist *)new_analysis->content)->state;

    while(tmp_state_clr)
    {
        t_list *nb_list = tmp_state_clr->content;
        lst_clr(&nb_list);
        t_g_list *tmp_next = tmp_state_clr->next;
        free(tmp_state_clr);
        tmp_state_clr = tmp_next;
    }
    lst_g_clr(&(((t_path_dist *)new_analysis->content)->instruct));
    free(new_analysis->content);
    free(new_analysis);*/
}

int q = 0;

void    reinitialise(t_list **tmp_a, t_list **tmp_b, int *tmp_nb, int nb_instruct, t_list **lst_a_ori, t_list **lst_b)
{
    if (!current_path)
    {
        current_path = malloc(sizeof(t_path_dist));
        current_path->instruct = NULL;
        current_path->state = NULL;
    }
    *tmp_a = ft_lstcpy(*lst_a_ori);
    *tmp_b = ft_lstcpy(*lst_b);
    *tmp_nb = nb_instruct + 1;
    t_g_list *state = ft_list_lstnew(ft_lstcpy(*lst_a_ori), sizeof(t_list *));
    ft_g_lstappend(&(current_path->state), state);
}

int test_new(char *fail, int *sorted, t_list **lst_a_ori, t_list **lst_b, int len_ori, int *nb_instruct)
{
    t_list *nb_instruct_lst;
    t_list *tmp_a;
    t_list *tmp_b;
    int     tmp_nb;

    char *past_instruct;
    nb_instruct_lst = NULL;

    printf("exit\n");
    exit(1);

    if (ft_strcmp(fail, "sa") && (*lst_a_ori) && (*lst_a_ori)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31msa - New 1\n\n\033[0m");
        swap(tmp_a);
        past_instruct = ft_strdup("sa");
        t_g_list *test = ft_g_lstnew("sa", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "sb") && (*lst_b) && (*lst_b)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31msa - New 1\n\n\033[0m");
        swap(tmp_b);
        past_instruct = ft_strdup("sb");
        t_g_list *test = ft_g_lstnew("sb", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "ss") && ft_strcmp(fail, "sa") && ft_strcmp(fail, "sb") && (*lst_a_ori) && (*lst_a_ori)->next && (*lst_b) && (*lst_b)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31msa - New 1\n\n\033[0m");
        swap(tmp_a);
        swap(tmp_b);
        past_instruct = ft_strdup("ss");
        t_g_list *test = ft_g_lstnew("ss", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "rra") && *lst_a_ori && (*lst_a_ori)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mra - New 2\n\n\033[0m");
        rotate(1, &tmp_a);
        past_instruct = ft_strdup("ra");
        t_g_list *test = ft_g_lstnew("ra", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "rrb") && *lst_b && (*lst_b)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mra - New 2\n\n\033[0m");
        rotate(1, &tmp_b);
        past_instruct = ft_strdup("rb");
        t_g_list *test = ft_g_lstnew("rb", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "rra") && ft_strcmp(fail, "rrb") && ft_strcmp(fail, "rrr") && *lst_a_ori && (*lst_a_ori)->next && *lst_b && (*lst_b)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mra - New 2\n\n\033[0m");
        rotate(1, &tmp_a);
        rotate(1, &tmp_b);
        past_instruct = ft_strdup("rr");
        t_g_list *test = ft_g_lstnew("rr", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "ra") && *lst_a_ori && (*lst_a_ori)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mrra - New 3\n\n\033[0m");
        rotate(0, &tmp_a);
        past_instruct = ft_strdup("rra");
        t_g_list *test = ft_g_lstnew("rra", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "rb") && *lst_b && (*lst_b)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mrra - New 3\n\n\033[0m");
        rotate(0, &tmp_b);
        past_instruct = ft_strdup("rrb");
        t_g_list *test = ft_g_lstnew("rrb", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "ra") && ft_strcmp(fail, "rb") && ft_strcmp(fail, "rr") && *lst_a_ori && (*lst_a_ori)->next && *lst_b && (*lst_b)->next)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mrra - New 3\n\n\033[0m");
        rotate(0, &tmp_a);
        rotate(0, &tmp_b);
        past_instruct = ft_strdup("rrr");
        t_g_list *test = ft_g_lstnew("rrr", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "pb") && *lst_b)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mpa - New 4\n\n\033[0m");
        push(&tmp_a, &tmp_b);
        past_instruct = ft_strdup("pa");
        t_g_list *test = ft_g_lstnew("pa", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
        //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));

    if (ft_strcmp(fail, "pa") && *lst_a_ori)
    {
        reinitialise(&tmp_a, &tmp_b, &tmp_nb, *nb_instruct, lst_a_ori, lst_b);
        ft_putstr("\033[31mpb - New 5\n\n\033[0m");
        push(&tmp_b, &tmp_a);
        past_instruct = ft_strdup("pb");
        t_g_list *test = ft_g_lstnew("pb", 3); //ca marchait pas si je le mettais direct dedans
        ft_g_lstappend(&(current_path->instruct), test);
         //leak surement quelque part
        do_new(&nb_instruct_lst, sorted, &tmp_a, &tmp_b, len_ori, past_instruct, &tmp_nb);
    }
    else
        ft_lstappend(&nb_instruct_lst, ft_lstnew(0));
    return (0);
}