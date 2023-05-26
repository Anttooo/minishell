
#include "../../include/input.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data g_data;

char	*handle_unclosed_quote(char *input, int mode)
{
	char	*new_input;
	int		i;
	char	*buffer;
	char	*temp;

	buffer = malloc(1);
	buffer[0] = '\0';
	while (mode != DEFAULT_MODE)
	{
		i = 0;
		// Get a single line of new_input
		new_input = readline("> ");
		// go through each character in new_input with is_mode_changing_char
		while (new_input[i] != '\0')
		{
			is_mode_changing_char(new_input[i], &mode);
			i++;
		}
		// Append the new_input to buffer
		temp = malloc(ft_strlen(buffer) + ft_strlen(new_input) + 2);
		// add error handling
		ft_strlcpy(temp, buffer, ft_strlen(buffer) + 1); // Copy buffer into temp
		ft_strlcat(temp, "\n", ft_strlen(buffer) + ft_strlen("\n") + 1); // add newline into temp (it will also be the first thing in empty buffer)
		ft_strlcat(temp, new_input, ft_strlen(temp) + ft_strlen(new_input) + 1); // add new_input to temp
		free (buffer); // free the old buffer
		buffer = temp; // buffer now includes the previous buffer + newline + new_input
		free(new_input); // free new_input
	}
	temp = malloc(ft_strlen(input) + ft_strlen(buffer) + 1); // temp gets space for input + buffer
	// add error handling
	ft_strlcpy(temp, input, ft_strlen(input) + 1); // Copy input into temp
	ft_strlcat(temp, buffer, ft_strlen(temp) + ft_strlen(buffer) + 1); // append buffer into temp
	free(input); // free the original input
	free(buffer); // free the buffer
	return (temp); // pass back the temp containing both
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
		{
			// printf("Heredoc should be handled here\n");
			// get_delim();
			// heredoc(delim);
			// If there isn't a delim after <<, "syntax error near unexpected token `newline'"
			return (HEREDOC_MODE);
		}
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
		printf("Heredoc\n");
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
