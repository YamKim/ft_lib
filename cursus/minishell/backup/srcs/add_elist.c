#include "../incs/minishell.h"

int			add_elist(
			t_list **list_head,
			char *key, char *val)
{
	t_list	*tmp;
	t_env	*tmp_env;

	printf("KEY: %s, VALUE: %s\n", key, val);
	if(list_head == 0)
		return (1);
	if (!(tmp_env = (t_env *)malloc(sizeof(t_env))))
		return (1);
	if (!(tmp_env->key = ft_strdup(key)))
		return (1);
	if (!(tmp_env->val = ft_strdup(val)))
		return (1);
	tmp = ft_lstnew(tmp_env); 
	ft_lstadd_back(list_head, tmp);
	return (0);
}
