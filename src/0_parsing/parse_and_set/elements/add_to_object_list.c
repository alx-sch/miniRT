#include "main.h"

/*Adds an object to the linked list of objects.*/
int	add_to_object_list(t_scene **scene, t_obj **obj)
{
	t_list	*obj_node;

	obj_node = ft_lstnew(*obj);
	if (!obj_node)
	{
		free(obj);
		return (ERR_MEM_ALLOC);
	}
	ft_lstadd_back(&(*scene)->objs, obj_node);
	return (0);
}
