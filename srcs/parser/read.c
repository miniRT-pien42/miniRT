#include "ft_deque.h"
#include "get_next_line.h"
#include "libft.h"
#include "result.h"
#include "scene.h"
#include <fcntl.h> // open
#include <stdlib.h>

static t_deque	*read_lines(const int fd)
{
	t_deque			*lines;
	char			*line;
	t_result		result;
	t_deque_node	*node;

	lines = deque_new();
	while (true)
	{
		line = get_next_line(fd, &result); // todo: if result==FAILURE
		if (line == NULL)
			break ;
		// todo: remove last newline?
		node = deque_node_new((void *)line);
		deque_add_back(lines, node);
	}
	return (lines);
}

t_deque	*read_file(const char *file_name)
{
	int		fd;
	t_deque	*lines;

	fd = open(file_name, O_RDONLY); // todo: create x_open with error handle
	lines = read_lines(fd);
	return (lines);
}

static bool	starts_with_specified_prefixes(const char *line, const char **types)
{
	const size_t	len_types = ft_len_2d_array(types);
	size_t			i;

	i = 0;
	while (i < len_types)
	{
		if (ft_strncmp(line, types[i], ft_strlen(types[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	starts_with_valid_identifier(t_deque *lines)
{
	t_deque_node		*node;
	char				*line;
	static const char	*all_types[] = {TYPE_AMBIENT, TYPE_CAMERA, TYPE_LIGHT, \
								TYPE_PLANE, TYPE_SPHERE, TYPE_CYLINDER, NULL};

	node = lines->node;
	while (node)
	{
		line = (char *)node->content;
		if (!starts_with_specified_prefixes(line, all_types))
		{
			deque_clear_all(&lines, free);
			return (false);
		}
		node = node->next;
	}
	return (true);
}

void	split_line_with_space(t_deque *lines)
{
	t_deque_node	*node;
	char			*line;
	char			**split_line;

	node = lines->node;
	while (node)
	{
		line = (char *)node->content;
		split_line = ft_split((const char *)line, ' ');
		ft_free((void **)&line);
		node->content = (void *)split_line;
		node = node->next;
	}
}
