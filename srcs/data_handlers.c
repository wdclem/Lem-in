#include "lemin.h"

t_info	*get_info(void)
{
	static t_info	info;

	return (&info);
}

t_room **get_rooms(void)
{
	static t_room	**rooms;

	return (rooms);
}

t_name *get_room_names (void)
{
	static t_name	*names;

	return (names);
}

int	name_to_id(char *name)
{
	//check the list of names for match
	t_name	*names;
	int		id;

	names = get_room_names();
	(void)names;
	(void)name;

	//magic
	id = 0;
	return (id);
}

int room_to_id(t_room *room)
{
	t_room	**rooms;

	rooms = get_rooms();
	return ((int)(*rooms - room));
}

t_room *id_to_room(int id)
{
	t_room	**rooms;

	rooms = get_rooms();
	return(rooms[id]);
}

t_name id_to_name(int id)
{
	t_name	*names;

	names = get_room_names();
	return (names[id]);
}

static int *get_room_count_ptr(void)
{
	static int	*ptr;

	return (ptr);
}

void increment_room_count(void)
{
	int	*ptr;

	ptr = get_room_count_ptr();
	(*ptr)++;
}

int get_room_count(void)
{
	return (*get_room_count_ptr());
}

t_bool	is_occupied(t_room room)
{
	(void)room;
	//check if there's an ant in the room
	return (0);
}

t_bool	is_visited(t_room room)
{
	(void)room;
	//check if this room was already visited during search
	return (0);
}

t_room	*go_to_room(t_room *cur_room, t_link_id *link_id)
{
	if (room_to_id(cur_room) == link_id->left)
		return (id_to_room(link_id->left));
	return (id_to_room(link_id->right));
}

int can_read_file(void)
{
	return (0);
}

/*
t_room *cur_room;
t_room *next_room;

for each link in cur_room
	next_room = get_next_room(cur_room, cur_room->link_ids[i]);

*/
