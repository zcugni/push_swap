/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:36:28 by zcugni            #+#    #+#             */
/*   Updated: 2018/02/02 17:36:29 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Gestion des doublons
int h = 0;
extern t_g_list *analysis;
#include <stdio.h>

int	define_instruct(int *sorted, t_list **lst_a_ori, t_list **lst_a_current, t_list **lst_b, int *len_current, int len_ori, int first, char **past_instruct, int *nb_instruct, int elem_i) //const pour sorted ?
{
	int		up;
	int 	down;
	int		next_up;
	int		next_down;
	int		dist_up;
	int		dist_down;
	int		next_dist_up;
	int		next_dist_down;
	int		first_in_lst;
	int		make_sa;
	int		make_sb;
	int		make_ra;
	int		make_rb;
	int		make_rra;
	int		make_rrb;
	int		make_pa;
	int		make_pb;

	////// Debug : /////


	h++;
	//if (h > 15)
	//	return (0);

	if (first)
	{
		t_list *tmp = *lst_a_ori;
		printf("A : ");
		while (tmp)
		{
			printf("%i ", tmp->nb);
			tmp = tmp->next;
		}
		printf("\n");
		tmp = *lst_b;
		printf("B : ");
		while (tmp)
		{
			printf("%i ", tmp->nb);
			tmp = tmp->next;
		}
		printf("\n");
	}

	///// A faire : /////
	// * doublons

	if (!lst_a_current)
		lst_a_current = lst_a_ori;

	make_sa = 0;
	make_sb = 0;
	make_ra = 0;
	make_rb = 0;
	make_rra = 0;
	make_rrb = 0;
	make_pa	= 0;
	make_pb = 0;

	up = get_up((*lst_a_current)->nb, sorted, len_ori);
	dist_up = get_up_dist((*lst_a_current)->nb, up, *lst_a_ori, *len_current);
	down = get_down((*lst_a_current)->nb, sorted, len_ori);
	dist_down = get_down_dist((*lst_a_current)->nb, down, *lst_a_ori, *len_current);

	if ((*lst_a_current)->next)
	{
		next_up = get_up((*lst_a_current)->next->nb, sorted, len_ori);
		next_dist_up = get_up_dist((*lst_a_current)->next->nb, next_up, *lst_a_ori, *len_current);
		next_down = get_down((*lst_a_current)->next->nb, sorted, len_ori);
		next_dist_down = get_down_dist((*lst_a_current)->next->nb, next_down, *lst_a_ori, *len_current);
		//valeur par defaut si next existe pas ?
	}
	
	if ((*lst_a_current)->nb == (*lst_a_ori)->nb)
		first_in_lst = 1;
	else
		first_in_lst = 0;

	if (first_in_lst &&
			((dist_down == -2 && dist_up != -1) ||
			(dist_up == -2 && dist_down != 1) ||
			(dist_down == -1 && (dist_up > 2 || dist_up < -2)) ||
			((*lst_a_current)->nb == sorted[*len_current] && (*lst_a_current)->next->next->nb == sorted[0])) //protect next->next
	)
	{
		make_sa = 1;
	}

	if (first_in_lst && dist_up == -2 && dist_down == 1 && (*lst_a_current)->nb > (*lst_a_current)->next->nb)
		make_sa = 1;

	//je devrais pas mettre first_in_lst btw ?
	if (first_in_lst && (*lst_a_current)->nb == (*lst_a_ori)->next->nb && dist_up == 100) //je suis pas sure de cette condition, il pourrait y avoir des variantes
		make_sa = 1;



	//pa
	if (!make_sa && first_in_lst && *lst_b)
		if ((dist_up == -1 || dist_up == 0) && (*lst_b)->nb == down)
			make_pa = 1;

	//faudra rajouter les rb/rrb quand leurs conditions seront differentes
	if (!make_sa && !make_pa && first_in_lst && (*lst_a_current)->next)
	{
		// C'est assez arbitraire pour l'instant mais j'arrive pas a plus generalise
		if (dist_up == -1 && next_dist_up == 2)
			make_pb = 1;
		else if (dist_down == -1 && dist_up == 2)
			make_pb = 1;
		else if (dist_down == 0 && dist_up == 100) //arf non
			make_pb = 1;
		else if (dist_up == 1 && next_dist_down == -2)
			make_pb = 1;
	}


	//ra - rra
	if (!make_pb && !make_sa && dist_up != -1 && dist_up != 0) //je suis pas 100% pour le !make_sa mais je prefere etre secu
	{
		if (
			//si le non-tri est au debut de la liste, mais que l'element cherche ce trouve tout a la fin
			//dans mes exemples c'est que des dists_up, mais en vrai ca devrait etre pareil pour des down aussi non ?			
			(first_in_lst && (dist_up == 1 || dist_up == 2))
			|| (dist_up == 2 && (*lst_a_current)->nb == (*lst_a_ori)->next->nb)
			|| elem_i >= len_ori / 2 //le non-tri vers la fin
		)
		{
			make_rra = 1;
		}
		else //else tout court ? (non-tri vers le debut)
		{
			make_ra = 1;
		}
	}
	else if (!make_pb && !make_sa && !(*lst_a_current)->next && (*lst_a_current)->nb != sorted[len_ori - 1]) //si on est a la fin, et que donc tout est trie
	{
		if (ft_lstfind_i(*lst_a_ori, sorted[len_ori - 1]) >= len_ori / 2)
			make_rra = 1;
		else
			make_ra = 1;
	}

	//ce sera pas ca a la fin mais j'ai pas assez d'info pour le moment
	if (*lst_b && (*lst_b)->next && (*lst_b)->nb < (*lst_b)->next->nb)
	{
		if (make_ra)
			make_rb = 1;
		else if (make_rra)
			make_rrb = 1;
	}



	if (make_sa || make_sb)
	{
		if (make_sa)
		{
			if (!ft_strcmp((const char *)*past_instruct, "sa"))
				return (test_new("sa", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
			*past_instruct = ft_strdup("sa");
			swap(*lst_a_ori);
		}
		if (make_sb)
		{
			if (!ft_strcmp((const char *)*past_instruct, "sb"))
				return (test_new("sb", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
			*past_instruct = ft_strdup("sb");
			swap(*lst_b);
		}
		if (make_sa && make_sb)
			*past_instruct = ft_strdup("ss");
		printf("%s\n", *past_instruct);
		(*nb_instruct)++;
		return (1);
	}
	else if (make_ra || make_rb)
	{
		if (make_ra)
		{
			if (!ft_strcmp((const char *)*past_instruct, "rra"))
				return (test_new("ra", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
			*past_instruct = ft_strdup("ra");
			rotate(1, lst_a_ori);
		}
		if (make_rb)
		{
			if (!ft_strcmp((const char *)*past_instruct, "rrb"))
				return (test_new("rb", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
			*past_instruct = ft_strdup("rb");
			rotate(1, lst_b);
		}
		if (make_ra && make_rb)
			*past_instruct = ft_strdup("rr");
		printf("%s\n", *past_instruct);
		(*nb_instruct)++;
		return (1);
	}
	else if (make_rra || make_rrb)
	{
		if (make_rra)
		{
			if (!ft_strcmp((const char *)*past_instruct, "ra"))
				return (test_new("rra", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
			*past_instruct = ft_strdup("rra");
			rotate(0, lst_a_ori);
		}
		if (make_rrb)
		{
			if (!ft_strcmp((const char *)*past_instruct, "rb"))
				return (test_new("rrb", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
			*past_instruct = ft_strdup("rrb");
			rotate(0, lst_b);
		}
		if (make_rra && make_rrb)
			*past_instruct = ft_strdup("rrr");
		printf("%s\n", *past_instruct);
		(*nb_instruct)++;
		return (1);
	}
	else if (make_pa)
	{
		if (!ft_strcmp((const char *)*past_instruct, "pb"))
			return (test_new("pa", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
		*past_instruct = ft_strdup("pa");
		push(lst_a_ori, lst_b);
		printf("%s\n", *past_instruct);
		(*nb_instruct)++;
		return (1);
	}
	else if (make_pb)
	{
		if (!ft_strcmp((const char *)*past_instruct, "pa"))
				return (test_new("pb", sorted, lst_a_ori, lst_b, len_ori, nb_instruct));
		*past_instruct = ft_strdup("pb");
		push(lst_b, lst_a_ori);
		printf("%s\n", *past_instruct);
		(*nb_instruct)++;
		return (1);
	}

	/// Aucun des cas, on continue sur le prochain ////
	elem_i++;
	if ((*lst_a_current)->next)
		return (define_instruct(sorted, lst_a_ori, &((*lst_a_current)->next), lst_b, len_current, len_ori, 0, past_instruct, nb_instruct, elem_i));
		
	/// Trie ///
	return (0);
}

int main(int argc, char **argv)
{
	int     i;
	t_list  *lst_a;
	t_list	*lst_b;
	int     *sorted;
	int     tmp;
	int		res;
	int		nb_instruct = 0;

	char	*past_instruct;

	i = 1;
	past_instruct = ft_strdup("ii");
	res = 1;
	if (argc > 1)
	{
		sorted = malloc((argc - 1) * sizeof(int));
		while (argv[i])
		{
			tmp = ft_atoi(argv[i]);
			sorted[i - 1] = tmp;
			i++;
			ft_lstappend(&lst_a, ft_lstnew(tmp));
		}
		quicksort(sorted, i - 1);
		int len = i - 1;
		
		int j = 0;
		while (res)
		{
			res = define_instruct(sorted, &lst_a, NULL, &lst_b, &len, i -1, 1, &past_instruct, &nb_instruct, 0);
			printf("\n");
			j++;
		}
			
		while (lst_a)
		{
			printf("%i ", lst_a->nb);
			lst_a = lst_a->next;
		}
		printf("\n");
		printf("nb_instructs : %i\n", j - 1);
		/*t_g_list *tmp_analysis = analysis;
   		while (tmp_analysis)
    	{
			//printf("plop\n");
			if (((t_path_dist *)tmp_analysis->content)->dist != 100)
			{
				printf("path (%i inst) : ", ((t_path_dist *)tmp_analysis->content)->dist);
				t_g_list *tmp_instruct = ((t_path_dist *)tmp_analysis->content)->instruct;
				while (tmp_instruct)
				{
					printf("%s ", (char *)(tmp_instruct->content));
					tmp_instruct = tmp_instruct->next;
				}
				printf("\n");
			
				printf("states : \n");
				t_g_list *tmp_state = ((t_path_dist *)tmp_analysis->content)->state;
				while (tmp_state)
				{
					t_list *tmp_nb = tmp_state->content;
					while (tmp_nb)
					{
						printf("%i ", tmp_nb->nb);
						tmp_nb = tmp_nb->next;
					}
					tmp_state = tmp_state->next;
					printf("\n");
				}
				printf("\n");
			}
			tmp_analysis = tmp_analysis->next;
    	}*/
	}
	return (0);    
}
