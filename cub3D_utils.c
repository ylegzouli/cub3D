int		is_id(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (1);
	if (line[0] == 'N' && line[1] == 'O')
		return (2);
	if (line[0] == 'S' && line[1] == 'O')
		return (3);
	if (line[0] == 'W' && line[1] == 'E')
		return (4);
	if (line[0] == 'E' && line[1] == 'A')
		return (5);
	if (line[0] == 'S' && line[1] == ' ')
		return (6);
	if (line[0] == 'F' && line[1] == ' ')
		return (7);
	if (line[0] == 'C' && line[1] == ' ')
		return (8);
	else
		return (0);
}

int		is_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == '1')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

void	get_size_map(t_list *li)
{
	
