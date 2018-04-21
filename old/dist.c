//Je sais pas si je vais tout garder et je pourrais surement en fusionner certaines, mais je mets ici en attendant
#include "push_swap.h"

int		get_up(int nb, int *sorted, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (sorted[i] == nb && i != len - 1)
			return (sorted[i + 1]);
		i++;
	}
	return (nb);
}

int		get_down(int nb, int *sorted, int len)
{
	int i;

	i = 0;
	if (sorted[i] == nb)
		return (sorted[i++]);
	while (i < len)
	{
		if (sorted[i] == nb)
			return (sorted[i - 1]);
		i++;
	}
	return (nb);
}

int		get_down_dist(int nb, int down, t_list *lst_a, int len)
{
	t_list *tmp;
	int		i;
	int		nb_index;
	int		down_index;

	tmp = lst_a;
	i = 0;
	down_index = -1;
	nb_index = -1;
	while (tmp && (down_index == -1 || nb_index == -1))
	{
		if (tmp->nb == nb)
			nb_index = i;
		if (tmp->nb == down)
			down_index = i;
		i++;
		tmp = tmp->next;
	}
	if (down_index == -1)
		return (100);
	if (down_index > nb_index)
	{
		if (abs(nb_index - down_index) < abs(len - down_index + nb_index))
			return (nb_index - down_index);
		else
			return (len - down_index + nb_index);
	}
	else
	{
		if (abs(nb_index - down_index) <= abs(len - nb_index + down_index))
			return (nb_index - down_index);
		else
			return (-(len - nb_index + down_index));
	}
}

// En soit je m'en fiche de la distance, je veux juste savoir si elle est en dehors ou dans la range -2 / 2
// Donc j'aurais pas besoin de parcourir autant la liste

int		get_up_dist(int nb, int up, t_list *lst_a, int len)
{
	t_list *tmp;
	int		i;
	int		nb_index;
	int		up_index;

	tmp = lst_a;
	i = 0;
	up_index = -1;
	nb_index = -1;
	while (tmp && (up_index == -1 || nb_index == -1))
	{
		if (tmp->nb == nb)
			nb_index = i;
		if (tmp->nb == up)
			up_index = i;
		i++;
		tmp = tmp->next;
	}
	if (up_index == -1)
		return (100); // Mieux gerer ca (ca ira avec l'amelio du comm en dessus)
	if (up_index > nb_index)
	{
		if (abs(nb_index - up_index) <= abs(len - up_index + nb_index))
			return (nb_index - up_index);
		else
			return (len - up_index + nb_index);
	}
	else
	{
		if (abs(nb_index - up_index) <= abs(len - nb_index + up_index))
			return (nb_index - up_index);
		else
			return (-(len - nb_index + up_index));
	}
}