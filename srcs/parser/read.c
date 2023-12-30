#include "ft_deque.h"
#include "helpers.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <fcntl.h> // open_flag
#include <unistd.h>

static t_deque	*read_lines(const int fd)
{
	t_deque			*lines;
	char			*line;
	t_deque_node	*node;

	lines = deque_new();
	while (true)
	{
		line = x_get_next_line(fd);
		if (line == NULL)
			break ;
		node = deque_node_new((void *)line);
		deque_add_back(lines, node);
	}
	return (lines);
}

t_deque	*read_file(const char *file_name)
{
	int		fd;
	t_deque	*lines;

	fd = x_open(file_name, O_RDONLY);
	lines = read_lines(fd);
	close(fd);
	return (lines);
}

static bool	starts_with_specified_prefixes(const char *line, const char **types)
{
	const size_t	len_types = ft_len_2d_array(types);
	size_t			i;

	if (line == NULL)
		return (false);
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
	char				**line;
	static const char	*all_types[] = {TYPE_AMBIENT, TYPE_CAMERA, TYPE_LIGHT, \
								TYPE_PLANE, TYPE_SPHERE, TYPE_CYLINDER, NULL};

	node = lines->node;
	while (node)
	{
		line = (char **)node->content;
		if (!starts_with_specified_prefixes(line[0], all_types))
			return (false);
		node = node->next;
	}
	return (true);
}

// split lines with white-space.
void	split_lines(t_deque *lines)
{
	t_deque_node	*node;
	char			*line;
	char			**split_line;

	if (deque_is_empty(lines))
		return ;
	node = lines->node;
	while (node)
	{
		line = (char *)node->content;
		split_line = ft_split((const char *)line, DELIMITER_WHITE_SPACE);
		ft_free((void **)&line);
		node->content = (void *)split_line;
		node = node->next;
	}
}
