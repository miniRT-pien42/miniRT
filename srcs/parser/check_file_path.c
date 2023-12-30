#include "helpers.h"
#include "libft.h"
#include "parse.h"
#include <fcntl.h> // open_flag
#include <stdio.h>
#include <unistd.h>

static char	*find_head_extention_pointer(\
								const char *filepath, const size_t len_filepath)
{
	return (ft_strnstr(filepath, FILE_EXTENSION, len_filepath));
}

static bool	ends_with_single_extension(\
						const char *extension_ptr, const size_t len_filepath)
{
	return (ft_strncmp(extension_ptr, FILE_EXTENSION, len_filepath) == 0);
}

// check hidden file or not. (.rt, /.rt)
static bool	is_valid_filetype(const char *filepath, const char *extension_ptr)
{
	if (filepath == extension_ptr)
		return (false);
	if (*(extension_ptr - 1) == '/')
		return (false);
	return (true);
}

static bool	is_file_exist(const char *filepath)
{
	int	fd;

	fd = x_open(filepath, O_RDONLY);
	close(fd);
	return (true);
}

bool	is_valid_file_path(const char *filepath)
{
	const size_t	len_filepath = ft_strlen(filepath);
	const char		*extension_ptr = \
							find_head_extention_pointer(filepath, len_filepath);

	if (extension_ptr == NULL)
		return (false);
	if (!ends_with_single_extension(extension_ptr, len_filepath))
		return (false);
	if (!is_valid_filetype(filepath, extension_ptr))
		return (false);
	if (!is_file_exist(filepath))
		return (false);
	return (true);
}
