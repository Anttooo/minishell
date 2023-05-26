

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern	t_data g_data;

// Handles the expansion mode
// Turn off expansion mode and continue evaluating chars as usual
// The length of the env_var is checked to handle special case where $ is not followed by anything
void	handle_expansion_mode(int *mode, int *i)
{
	int		j;
	char	*expanded_value;
	char	*env_var;

	j = *i + 1;
	if (is_valid_first_character(g_data.cur.raw[j]))
		j++;
	while (is_valid_subsequent_character(g_data.cur.raw[j]))
		j++;
	env_var = ft_substr(g_data.cur.raw, (*i + 1), (j - 1) - *i);
	if (ft_strlen(env_var) > 0)
	{
		*i = j - 1;
		expanded_value = fetch_env_var(env_var);
		if (expanded_value)
		{
			j = 0;
			while (expanded_value[j] != '\0')
			{
				printf("Adding char to buffer: %c\n", expanded_value[j]);
				add_char_to_buffer(expanded_value[j]);
				j++;
			}
		}
	}
	else
		add_char_to_buffer('$');
	free(env_var);
	*mode -= 10;
}

// Check if the character is a letter or underscore
int is_valid_first_character(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') 
        return 1;
    return 0;
}

// Check if the character is a letter, digit, or underscore
int is_valid_subsequent_character(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
        return 1;
    return 0;
}

// Fetch environment variable
char	*fetch_env_var(char *str) {
	int idx;
	int len;
	char *needle;
	
	idx = 0;
	needle = ft_strjoin(str, "=");
	len = ft_strlen(needle);
	free(str);
	while(g_data.env.vars[idx] != NULL) {
		if (ft_strncmp(g_data.env.vars[idx],  needle, len) == 0)
			break;
		idx++;
	}
	int word_len = ft_strlen(g_data.env.vars[idx]) - len - 1;
	char *var = malloc((word_len + 1) * sizeof(char));
	if (!var)
		return (NULL);
	ft_memcpy(var, &g_data.env.vars[idx][len + 1], word_len);
	var[word_len] = '\0';
	return (var);
}
