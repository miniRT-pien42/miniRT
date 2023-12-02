#include "libft.h"

/* Returns bool true if s1 == s2, otherwise false.  */
/* If s1 or s2 is NULL, returns false.              */
bool	ft_streq(const char *s1, const char *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}
