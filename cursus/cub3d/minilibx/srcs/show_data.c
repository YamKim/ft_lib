#include "cub3d.h"

void	show_map_data(t_disp disp)
{
	char	val;
	printf("MAP DATA========================================\n");
	printf("map_height: %d\n", disp.map.height);
	for (int j = 0; j < disp.map.height; ++j)
	{
		for (int i = 0; disp.map.data[j][i] != MAP_BOARDER_VAL; ++i)
		{
			if (disp.map.data[j][i] == MAP_ROAD_VAL)
				val = MAP_ROAD;
			if (disp.map.data[j][i] == MAP_WALL_VAL)
				val = MAP_WALL;
			if (disp.map.data[j][i] == MAP_SPACE_VAL)
				val = MAP_SPACE;
			if (disp.map.data[j][i] == MAP_EXCEPTION_VAL)
				val = 'X';
			if (disp.map.data[j][i] == MAP_BOARDER_VAL)
				val = 'H';
			printf("%c", val);
		}
		printf("\n");
	}
}

void	show_lst_data(t_disp disp)
{
	t_lst	*itr;
	int		idx;

	itr = disp.spr_lst;
	idx = 0;
	printf("SPRITE DATA=====================================\n");
	while (itr)
	{
		printf("idx: %2d, spr.pos.x: %6.2lf, spr.pos.y: %6.2lf\n", idx++, itr->spr.pos.x, itr->spr.pos.y);
		itr = itr->next;
	}
}
