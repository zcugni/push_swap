#include "libft.h"

int		ft_pop_value(t_list **lst)
{
	t_list	*tmp;
	int		value;

	value = *((int *)(*lst)->content);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);
	return (value);
}
