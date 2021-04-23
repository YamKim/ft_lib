#include "../incs/philo.h"

#if 1
static void
	*is_all_eat(void *_info)
{
	int		idx;
	t_info	*info;

	info = (t_info *)_info;
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		if (!(info->philos[idx].eat_finished))
			if (sem_wait(info->philos[idx].eat_mutex))
				return (NULL);
				
		// unlock! for each philo's eat_mutex  before exit this program
	}
	if (sem_post(info->someone_dead_mutex))
		return (NULL);
	return (NULL);
}
#endif

int
	run_threads(t_info *info)
{
	int			idx;
	void		*philo;
	pthread_t	tid;

#if 1
	if (pthread_create(&tid, NULL, &is_all_eat, info))
		return (ERR_INIT_THREAD);
#endif
	idx = -1;
	info->beg_prog_time = get_cur_time();
	while (++idx < info->num_of_philos)
	{
		philo = (void *)(&info->philos[idx]);
		if (pthread_create(&tid, NULL, &run_routine, philo))
			return (ERR_INIT_THREAD);
		pthread_detach(tid);
		usleep(100);
	}
	return (0);
}

int
	main(int argc, char *argv[])
{
	t_info	info;

	init_info(&info, argc, argv);
	run_threads(&info);

#if 1
	if (info.someone_dead)
	{
		if (sem_wait(info.msg_mutex))
			return (1);
	}
#endif
	if (sem_wait(info.someone_dead_mutex))
		return (1);
	if (sem_post(info.someone_dead_mutex))
		return (1);
	usleep(10000);
	destroy_mutexes(&info);
	free_memory(&info);
	return (0);
}

#if 0
static void
	*is_all_eat(void *_info)
{
	int		idx;
	t_info	*info;

	info = (t_info *)_info;
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		if (!(info->philos[idx].eat_finished))
			pthread_mutex_lock(&info->philos[idx].eat_mutex);
		// unlock! for each philo's eat_mutex  before exit this program
	}
	pthread_mutex_unlock(&(info->someone_dead_mutex));
	return (NULL);
}
#endif
