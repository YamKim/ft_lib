#include "../incs/philo.h"

void
	do_die(t_info *info, t_philo *philo)
{
	show_message(philo, STATUS_DIE);
	info->someone_dead = 1;	
	pthread_mutex_lock(&(info->msg_mutex));
	pthread_mutex_unlock(&(info->someone_dead_mutex));
}