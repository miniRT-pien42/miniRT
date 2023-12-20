#include "ft_deque.h"
#include "get_next_line.h"
#include "libft.h"
#include "result.h"
#include <fcntl.h> // open

static void	add_split_line(t_deque *lines, char **line)
{
	char			**split_line_with_space;
	t_deque_node	*node;

	split_line_with_space = ft_split((const char *)*line, ' ');
	ft_free((void **)line);
	node = deque_node_new((void *)split_line_with_space);
	deque_add_back(lines, node);
}

static t_deque	*read_lines(const int fd)
{
	t_deque		*lines;
	char		*line;
	t_result	result;

	lines = deque_new();
	while (true)
	{
		line = get_next_line(fd, &result); // todo: if result==FAILURE
		if (line == NULL)
			break ;
		// todo: remove last newline?
		// todo: not allow head space
		add_split_line(lines, &line);
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
