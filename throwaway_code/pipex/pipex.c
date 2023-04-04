#include "pipex.h"

int	main(int argc, char **argv)
{
	t_data	data;

	// read command line arguments
	if (argc > 4)
	{
		if (parse_inputs(argc, argv, &data) == 1)
		{
			ft_printf("Issues while parsing inputs.\n");
			free_data(&data);
			return (1);
		}
	}
	else
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 ... cmdN outfile. Provide at least 4 arguments");
		return (1);
	}
	// check input file permissions
	if (access(data.infile, F_OK) == -1 || access(data.infile, R_OK) == -1) 
	{
		ft_printf("Missing permission for infile.\n");
		free_data(&data);
		return (1);
	}
	// open file for reading
	int input_fd = open(data.infile, O_RDONLY, 0644);
	if (input_fd == -1)
	{
		// TODO: create a function which does the clean exit for all end points
		ft_printf("Error opening input file.\n");
		free_data(&data);
		return (1);
	}

	// open file for writing
	int output_fd = open(data.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		// TODO: create a function which does the clean exit for all end points
		ft_printf("Error opening/creating output file.\n");
		free_data(&data);
		return (1);
	}
	// Use pipe to create a communication channel between the first and the second command
	if (pipe(data.pipe) < 0)
	{
		ft_printf("Error piping.\n");
		free_data(&data);
		return (1);
	}

	// use fork to create a child process which will execute the command in the first argument
	data.pid = fork();
	if (data.pid < 0)
	{
		printf("Fork failed\n");
		free_data(&data);
		return (1);
	}
	else if (data.pid == 0)
	{
		// child process code
		dup2(input_fd, STDIN_FILENO);
		dup2(data.pipe[1], STDOUT_FILENO);
		close(input_fd);
		close(output_fd);

		char *args[] = {"sh", "-c", data.commands[0], NULL};
		execve("/bin/sh", args, NULL);
	}
	else
	{
		// main process code
		wait(NULL);
		close(data.pipe[1]);
		close(input_fd);
    dup2(data.pipe[0], STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);
    char *args[] = {"sh", "-c", data.commands[1], NULL};
    execve("/bin/sh", args, NULL);
		close(output_fd);
	}
	free_data(&data);
	return (0);
}