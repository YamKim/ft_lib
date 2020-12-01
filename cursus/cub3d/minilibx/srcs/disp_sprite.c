#include "cub3d.h"

double	*g_perp_buf;
int		g_spr_cnt;

/*
** sprite setting
*/
void	set_sprite(t_pair *spr_pair, t_player player, t_lst *spr_lst)
{
	int	i;

	i = 0;
	while (i < g_spr_cnt)
	{
		spr_pair[i].order = i;
		spr_pair[i].dist = calc_dist(player.pos, spr_lst->spr.pos);
		++i;
	}	
}

t_vecd	get_spr_ray(t_player player, t_pair spr_pair, t_lst *spr_lst)
{
	t_vecd	ret;
	double	det;
	t_spr	spr;
	t_vecd	spr_dist;

	spr = lst_get_idx(spr_lst, spr_pair.order)->spr;
	spr_dist.x = spr.pos.x - player.pos.x;
	spr_dist.y = spr.pos.y - player.pos.y;
	det = calc_det(player.plane, player.dir);
	ret.x = (player.dir.y * spr_dist.x - player.dir.x * spr_dist.y) / det;
	ret.y = (-player.plane.y * spr_dist.x + player.plane.x * spr_dist.y) / det;
	return (ret);
}

void	sort_spr_pair(t_pair *spr_pair)
{
	int		i;
	int		j;
	double	remember;
	int		tmp_order;

	i = 1;
	while (i < g_spr_cnt)
	{
		remember = spr_pair[i].dist;
		j = i;
		while (--j >= 0 && remember > spr_pair[j].dist)
		{
			spr_pair[j + 1].dist = spr_pair[j].dist;
			spr_pair[j].dist = remember;
			tmp_order = spr_pair[j].order;
			spr_pair[j].order = spr_pair[j + 1].order;
			spr_pair[j + 1].order = tmp_order;
		}
		++i;
	}
}

void	set_draw_sprite(t_disp disp, t_draw *draw, t_vecd spr_ray_dist)
{
	int spr_width;

	draw->line_height = (int)fabs((double)disp.height / spr_ray_dist.y);	
	draw->beg = (int)fmax((double)(disp.height - draw->line_height) / 2, 0.0);
	draw->end = (int)fmin((double)(disp.height + draw->line_height) / 2, disp.height - 1);

	//spr_width = (int)fabs(SCREEN_HEIGHT / spr_ray_dist.y);
	spr_width = draw->line_height;
	draw->xbeg = (int)fmax((double)draw->xctr - (double)spr_width / 2 , 0.0);
	draw->xend = (int)fmin((double)draw->xctr + (double)spr_width / 2 , disp.width - 1);

	draw->y = draw->beg;
	draw->x = draw->xbeg;
}

void	draw_sprite_part(t_disp disp, t_tex tex, t_player player, t_draw draw)
{
	int	spr_width;
	int	tmp;
	int	color;

	spr_width = draw.line_height;
	while (draw.x < draw.xend)
	{
		draw.tx = (int)((256 * (draw.x - (draw.xctr - spr_width / 2)) \
							* tex.width / spr_width) / 256);
		if(player.sray_dist.y > 0 && draw.x > 0 && draw.x < disp.width \
			&& player.sray_dist.y < g_perp_buf[draw.x])
		{
			draw.y = draw.beg;
			while (draw.y < draw.end)
			{
				tmp = draw.y * 256 - disp.height * 128 + draw.line_height * 128;
				draw.ty = ((tmp * tex.height) / draw.line_height) / 256;
				color = tex.data[draw.ty * tex.width + draw.tx];
				if((color & 0x00FFFFFF) != 0)
					disp.img.data[draw.y * disp.width + draw.x] = color;
				++draw.y;
			}
		} ++draw.x;
	}
}

int		draw_sprite(t_disp disp, t_player player, t_hit hit_point, double *perp_buf)
{
	t_pair	*spr_pair;
	t_draw	draw;
	int		spr_width;
	t_tex	tex;
	int		i;

	g_perp_buf = perp_buf;
	g_spr_cnt = disp.spr_cnt;
	if (!(spr_pair = (t_pair *)malloc(sizeof(t_pair) * g_spr_cnt)))
		return (ERR_MALLOC);
	set_sprite(spr_pair, player, disp.spr_lst);
	sort_spr_pair(spr_pair);
	i = -1;
	while (++i < disp.spr_cnt)
	{
		player.sray_dist = get_spr_ray(player, spr_pair[i], disp.spr_lst);
		draw.xctr = (int)((double)disp.width / 2 \
							* (1 + player.sray_dist.x / player.sray_dist.y));
		set_draw_sprite(disp, &draw, player.sray_dist); 
		tex = disp.tex[lst_get_idx(disp.spr_lst, spr_pair[i].order)->spr.tex_nbr];
		draw_sprite_part(disp, tex, player, draw);
	}
	free(spr_pair);
	return (1);
}
