#include "libft.h"

t_list	*ft_pop(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew((*lst)->content, (*lst)->content_size);
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp);
	return (new);
}
