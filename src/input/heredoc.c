
#include "../../include/input.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data g_data;

int	heredoc_start_index(char *input)
{
	int i;
	int	mode;

	i = 0;
	mode = DEFAULT_MODE;
	while (input[i] != '\0')
	{
		is_mode_changing_char(input[i], &mode);
		if (input[i] == '<' && input[i + 1] == '<' && mode == DEFAULT_MODE)
			return (i);
		i++;
	}
	return (-1);
}

int	get_delim_start_index(char *input, int heredoc_start_idx)
{
	int delim_start_idx;
	int	i;

	i = heredoc_start_idx;
	while (input[i] && input[i] != '\0' && ft_isalpha(input[i]) == 0)
		i++;
	delim_start_idx = i;
	printf("Delim start idx: %d\n", delim_start_idx);
	return (delim_start_idx);
}


int		get_delim_end_index(char *input, int delim_start_idx)
{
	int	delim_end_idx;
	int	i;

	i = delim_start_idx;
	while (ft_isalnum(input[i]) == 1  && input[i] != '\0')
		i++;
	delim_end_idx = i;
	printf("Delim end idx: %d\n", delim_end_idx);
	return (delim_end_idx);
}

char	*heredoc_delim(char *input, int heredoc_start_idx)
{
	char	*delim;
	int		delim_start_idx;
	int		delim_end_idx;
	int		delim_len;

	delim_start_idx = get_delim_start_index(input, heredoc_start_idx);
	delim_end_idx = get_delim_end_index(input, delim_start_idx);
	delim_len = delim_end_idx - delim_start_idx;
	delim = ft_substr(input, delim_start_idx, delim_len);
	return (delim);
}

char	*handle_heredoc(char **input)
{
	// Find heredoc from input
	int	heredoc_start_idx;

	heredoc_start_idx = heredoc_start_index(*input);
	// Find the delim
	char	*delim;

	delim = heredoc_delim(*input, heredoc_start_idx);
	printf("Heredoc deliminator is: **%s**\n", delim);
	// Create temp file
	int fd = open("heredoc_temp_file", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
			perror("Error opening file");
			// TODO: add error handling here
	}
	// get input from user with readline(" >")
	char	*new_input;
	int		delim_found;

	delim_found = 0;
	while (delim_found == 0)
	{
		new_input = readline("> ");
		// Scan each line looking for delim and once there is a line with just the delim stop the loop
		if (ft_strncmp(new_input, delim, ft_strlen(new_input)) == 0)
			delim_found = 1;
		// write contents of new_input into the file
		if (delim_found == 0)
		{
			write(fd, new_input, ft_strlen(new_input));
			// TODO: handle errors here
			write(fd, "\n", 1);
			// TODO: handle errors here
		}
		free(new_input);
	}
	// Replace the '<< delim' with '< filename'
	
	// I am going to take first the part before the << = part_a and then the one after << delim = part_b
	char	*part_a;
	char	*part_b;
	int	delim_end_index;

	part_a = ft_substr(*input, 0, heredoc_start_idx);
	printf("Part_a: **%s**\n", part_a);

	delim_end_index = get_delim_end_index(*input, get_delim_start_index(*input, heredoc_start_idx));
	part_b = ft_substr(*input, delim_end_index, ft_strlen(*input) - delim_end_index);
	printf("Part_b: **%s**\n", part_b);

	// Now we have both of those parts, lets put it all together
	char	*combined;

	printf("Delim: %s\n", delim);

	combined = malloc(ft_strlen(part_a) + ft_strlen("heredoc_temp_file") + ft_strlen(part_b) + 3);
	printf("Malloced in total: %lu space\n", (ft_strlen(part_a) + ft_strlen("heredoc_temp_file") + ft_strlen(part_b) + 3));
	ft_strlcpy(combined, part_a, ft_strlen(part_a) + 1);
	ft_printf("Parsing new input: %s\n", combined);
	ft_strlcat(combined, "< ", ft_strlen(combined) + 3);
	ft_printf("Parsing new input: %s\n", combined);
	ft_strlcat(combined, "heredoc_temp_file", ft_strlen(combined) + ft_strlen("heredoc_temp_file") + 1);
	ft_printf("Parsing new input: %s\n", combined);
	ft_strlcat(combined, part_b, ft_strlen(combined) + ft_strlen(part_b) + 1);
	ft_printf("Parsing new input: %s\n", combined);
	// Flag that there is a heredoc temp file that needs to be deleted
	g_data.cur.heredoc_flag = 1;
	// close the file
	close(fd);
	free(delim);
	free(*input);
	if (part_a)
	{
		free(part_a);
		part_a = NULL;
	}
	if (part_b)
	{
		free(part_b);
		part_b = NULL;
	}
	return (combined);
}