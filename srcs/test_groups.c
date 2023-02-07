# include "../include/lemin.h"

t_path	*make_path(t_room **rooms, int cur_path[10], int *id)
{
	int path_len = 0;
	while (cur_path[path_len] >= 0) path_len++;
	if (path_len <= 0)
		return (NULL);
	t_path *new_path = open_path(path_len, id);
	for (int room_idx = 0; room_idx < new_path->len; room_idx++)
	{
		add_room_to_path(&new_path, rooms[cur_path[room_idx]], room_idx);
		printf(" * * adding room %s to path\n", rooms[cur_path[room_idx]]->id);
	}
	return (new_path);
}

t_pathgroup *make_group(t_room **rooms, int cur_group[10][10])
{
	int	id = 0;

	t_pathgroup *new_group = (t_pathgroup *)ft_memalloc(sizeof(t_pathgroup));
	int pathcount = 0;
	while (*cur_group[pathcount] >= 0) pathcount++;
	t_path **new_path_arr = (t_path **)ft_memalloc(sizeof(t_path *) * pathcount);
	for (int path_idx = 0; path_idx < pathcount; path_idx++)
	{
		printf(" * making path %d\n", path_idx);
		t_path *new_path = make_path(rooms, cur_group[path_idx], &id);
		new_path_arr[path_idx] = new_path;
		new_group->total_path_len += new_path->len;
	}
	new_group->len = pathcount;
	return (new_group);
}

t_pathgroup **get_pathgroups(t_info *info)
{
	t_pathgroup **new_group_arr;
	char *names[] = { "Aaa", "Bee", "Gee", "Eff", "Dee", "Jay", NULL };
	int room_count = 0;
	while (names[room_count] != NULL)
	{
		printf("found room named %s\n", names[room_count++]);
	}
    int groups[10][10][10] = {
		{
			{ 0, 4, 3, -1 },
			{-1}
		},
		{
			{0, 1, 2, 3, -1 },
			{0, 4, 5, 3, -1 },
			{-1}
		},
		{
			{-1}
		}
	};
    int groupcount = 0;
	while (groups[groupcount][0][0] >= 0)
	{
		groupcount++;
		printf("found group\n");
	}
	t_room **rooms = (t_room **)ft_memalloc(sizeof(t_room *) * room_count);
	for (int room_idx = 0; room_idx < room_count; room_idx++)
	{
		t_room *new_room = (t_room *)ft_memalloc(sizeof(t_room));
		new_room->id = ft_strdup(names[room_idx]);
		new_room->number = room_idx;
		new_room->occupied = 1;
		printf(" * making room %s\n", new_room->id);
		rooms[room_idx] = new_room;
	}
	info->start = rooms[0];
	info->end = rooms[room_count - 1];
	new_group_arr = (t_pathgroup **)ft_memalloc(sizeof(t_pathgroup *) * groupcount);

	for (int group_idx = 0; group_idx < groupcount; group_idx++)
	{
		printf("making group %d\n", group_idx);
		t_pathgroup *new_group = make_group(rooms, groups[group_idx]);
		new_group->id = group_idx;
		new_group_arr[group_idx] = new_group;
	}

	return (new_group_arr);
}
