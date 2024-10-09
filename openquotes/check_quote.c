#include <stdbool.h>
#include <stdio.h>

bool	check_quote(char *str)
{
	int		c_single;
	int		c_double;
	char	prev;
	char 	sec_prev;
	int		i;

	c_single = 0;
	c_double = 0;
	prev = '\0';
	sec_prev = '\0';
	i = 0;
	while  (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (prev == '"' && sec_prev == '\'')
				return (true);
			sec_prev = prev;
			prev = '\'';
			c_single++;
		}
		if (str[i] == '"')
		{
			if (prev == '\'' && sec_prev == '"')
				return (true);
			sec_prev = prev;
			prev = '"';
			c_double++;
		}
		i++;
	}
	if (c_single % 2 != 0 || c_double % 2 != 0)
		return (true);
	return (false);
}

int main(void)
{
	if (check_quote("\'salut\'\"\"\'\"\"\'"))
		printf("Quotes are mismatched or invalid.\n");
	else
		printf("Quotes are properly balanced.\n");

	return 0;
}