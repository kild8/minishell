if (check_redir(*input))
	{
		write(1, "Syntax error near <>\n", 21);
		return (true);
	}

bool	check_redir(char *str)
{
	int	c_r;
	int	c_l;
	int	i;

	c_r = 0;
	c_l = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (check_redir2(str + i, &c_l, &c_r, &i) == true)
			return (true);
		if (i > 0)
		{
		if (str[i] == '>')
			c_r = 1;
		}
		i++;
	}
	return (false);
}

bool	check_redir2(char *str, int *c_l, int *c_r, int *i)
{
		if (c_r = 1 && str[i] == '<')
			return (true);
		if (c_l = 1 && str[i] == '>')
			return (true);
		while (str[i] == '<' && str[i] != '\0')
		{
			c_l++;
			if (c_l > 2)
				return (true);
			i++;
		}
		while (str[i]== '>' && str[i] != '\0')
		{
			c_r++;
			if (c_r > 2)
				return (true);
			i++;
		}
		if (i > 0)
		{
			if (str[i - 1] == '<')
			c_l = 1;
		}
}
