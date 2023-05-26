
#include "../../include/input.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data g_data;

char	*update_multiline_buffer(char *buffer, char *new_input)
{
	char	*temp;

	temp = malloc(ft_strlen(buffer) + ft_strlen(new_input) + 2);
	// TODO: add error handling
	ft_strlcpy(temp, buffer, ft_strlen(buffer) + 1);
	ft_strlcat(temp, "\n", ft_strlen(buffer) + ft_strlen("\n") + 1);
	ft_strlcat(temp, new_input, ft_strlen(temp) + ft_strlen(new_input) + 1);
	free(buffer);
	free(new_input);
	return temp;
}

// Combines the original input with the buffer containing multiline input
char	*combine_input_and_multiline_buffer(char *input, char *buffer)
{
	char	*temp;

	temp = malloc(ft_strlen(input) + ft_strlen(buffer) + 1);
	// TODO: add error handling
	ft_strlcpy(temp, input, ft_strlen(input) + 1);
	ft_strlcat(temp, buffer, ft_strlen(temp) + ft_strlen(buffer) + 1);
	free(input);
	free(buffer);
	return (temp);
}

char	*handle_unclosed_quote(char *input, int mode)
{
	char	*new_input;
	int		i;
	char	*buffer;

	buffer = malloc(1);
	buffer[0] = '\0';
	while (mode != DEFAULT_MODE)
	{
		i = 0;
		new_input = readline("> ");
		while (new_input[i] != '\0')
		{
			is_mode_changing_char(new_input[i], &mode);
			i++;
		}
		buffer = update_multiline_buffer(buffer, new_input);
	}
	return (combine_input_and_multiline_buffer(input, buffer));
}

int is_multiline(char *input)
{
	int i;
	int	mode;

	i = 0;
	mode = DEFAULT_MODE;
	while (input[i] != '\0')
	{
		is_mode_changing_char(input[i], &mode);
		if (input[i] == '<' && input[i + 1] == '<' && mode == DEFAULT_MODE)
			return (HEREDOC_MODE);
		i++;
	}
	if (mode != DEFAULT_MODE)
	{
		return (mode);
	}
	return (0);
}

void	handle_multiline(char **input)
{
	int	mode;

	mode = is_multiline(*input); // 0 if not, 4 if heredoc
	if (mode == HEREDOC_MODE)
		printf("Heredoc isn't supported yet.\n");
	else if (mode == SINGLE_QUOTES_MODE || mode == DOUBLE_QUOTES_MODE)
	{
		*input = handle_unclosed_quote(*input, mode);
	}
}

// void heredoc(char *delim)


// Heredoc mode creates a temporary file and writes to it in append mode
// When the delim is found, the file is closed but it's kept until the command has been run.
// IF there are multiple heredocs, each overwrites the temporary file.
// The file is then deleted.
// The filename is saved as input for the command.
