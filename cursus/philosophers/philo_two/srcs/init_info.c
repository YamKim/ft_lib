#include "../incs/philo.h"

static int
	init_semaphores(t_info *info)
{
	int		idx;
	char	sem_name[255];

	info->fork_mutexes = ft_sem_open(SEM_FORK, info->num_of_philos);
	if (!info->fork_mutexes)
		return (ERR_SEM_OPEN);

	info->msg_mutex = ft_sem_open(SEM_MSG, 1);
	if (!info->msg_mutex)
		return (ERR_SEM_OPEN);


	idx = -1;
	while (++idx < info->num_of_philos)
	{
		memset(sem_name, 0, 255);
		gen_name_tag(sem_name, idx);
		info->philos[idx].eat_mutex = ft_sem_open(sem_name, 1);
		if (!(info->philos[idx].eat_mutex))
			return (ERR_SEM_OPEN);
		if (sem_wait(info->philos[idx].eat_mutex))
			return (ERR_SEM_DO);
	}

	info->someone_dead_mutex = ft_sem_open(SEM_SOMEONE_DEAD, 1);
	if (!info->someone_dead_mutex)
		return (ERR_SEM_OPEN);
	if (sem_wait(info->someone_dead_mutex))
		return (ERR_SEM_DO);
	return (0);
}

static int
	init_philos(t_info *info)
{
	int			idx;
			
	info->philos = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philos);
	if (!info->philos)
		return (ERR_INIT_INFO);
	idx = -1;
	while (++idx < info->num_of_philos)
	{
		info->philos[idx].status = STATUS_THINK;
		info->philos[idx].pos = idx + 1;
		info->philos[idx].beg_eat_time = get_cur_time();
//		info->philos[idx].lfork = idx;
//		info->philos[idx].rfork = (idx + 1) % info->num_of_philos;
		info->philos[idx].eat_cnt = 0;
		info->philos[idx].info = info;
		info->philos[idx].eat_finished = 0;
	}
	return (0);
}

int
	init_info(
	t_info *info,
	int argc,
	char *argv[])
{
	(void)argc;
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->num_of_must_eat = ft_atoi(argv[5]);
	//memset(info->eat_finished, 0, MAX_NUM_OF_PHILOS);
	info->someone_dead = 0;
	if (init_philos(info))
		return (ERR_INIT_INFO);
	return (init_semaphores(info));
}
