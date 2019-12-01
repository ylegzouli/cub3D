#include "parsing.h"

void		parse_file(char *av, t_parse **data)
{
	t_list	*li;
	t_list	*tmp;
	int		fd;
	int		ret;
	char	*line;

	fd = open(av, O_RDONLY);
	li = NULL;
	while (ret = get_next_line(fd, line))
	{
		tmp = ft_lstnew_malloc(line, ft_strlen(line));
		ft_lstadd_back(&li, tmp);
	}
	while (li->next != NULL)
	{
		if (is_id(li->content) == 1)
			parse_res(li, data)
		if (is_id(li->content) >= 2 && is_id(li->content) <= 6)
			parse_tex(li);
		if (is_id(li->content) == 7 || is_id(li->content == 8)
			parse_color(li);
		if (is_map_line(li->content) == 1)
			parse_map(li);
		li = li->next;
	}
//	ft_lstclear(&li, &free);
}

void		parse_res(t_list *li, t_parse **data)
{
	char	**split;

	split = ft_split(li->content, ' ');
	(*data)->res_x = ft_atoi(split[1]);
	(*data)->res_y = ft_atoi(split[2]);
}

void		parse_tex(t_list *li, t_parse **data)
{
	char	**split;

	split = ft_split(li->content, ' ');
	(*data)->tex_no = malloc(sizeof(char) * (ft_strlen(split[1]) + 1));
	if (is_id(split[0]) == 2)
		ft_strcpy((*data)->tex_no, split[1]);
	if (is_id(split[0]) == 3)
		ft_strcpy((*data)->tex_su, split[1]);
	if (is_id(split[0]) == 4)
		ft_strcpy((*data)->tex_we, split[1]);
	if (is_id(split[0]) == 5)
		ft_strcpy((*data)->tex_ea, split[1]);
	if (is_id(split[0]) == 6)
		ft_strcpy((*data)->tex_spr, split[1]);
}

void		parse_color(t_list *li, t_parse **data)
{
	char	**split;

	split = ft_split(&((li->content)[2]), ',');	
	if (is_id(li->content) == 7)
	{	
		(*data)->sol->r = ft_atoi(split[0]);
		(*data)->sol->g = ft_atoi(split[1]);
		(*data)->sol->b = ft_atoi(split[2]);
	}
	if (is_id(li->content) == 7)
	{
		(*data)->plafond->r = ft_atoi(split[0]);
		(*data)->plafond->g = ft_atoi(split[1]);
		(*data)->plafond->b = ft_atoi(split[2]);
	}
}

void		parse_map(t_list *li, t_map **map )
{
	int		i;
	int		j;

	j = 0;
	(*((*map)->map)) = malloc(sizeof(char *) * ((*map)->size_y + 1));
	while (j < (*map)->size_y)
	{
		((*map)->map)[j] = malloc(sizeof(char) * ((*map)->size_x + 1);


}





