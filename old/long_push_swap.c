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

int main(int argc, char **argv)
{
	int     i;
	t_list  *lst_a;
	t_list	*lst_b;
	int     *sorted;
	int     tmp;
	int		res;
	int		nb_instruct = 0;

	i = 1;
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
			res = test_new("ii", sorted, &lst_a, &lst_b, len, &nb_instruct);
			printf("\n");
			j++;
		}	
		/*while (lst_a)
		{
			printf("%i ", lst_a->nb);
			lst_a = lst_a->next;
		}
		printf("\n");
		printf("nb_instructs : %i\n", j - 1);*/
		t_g_list *tmp_analysis = analysis;
   		while (tmp_analysis)
    	{
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
			//}
			tmp_analysis = tmp_analysis->next;
    	}
	}
	ft_get_leaks("end main\n");
	return (0);    
}
