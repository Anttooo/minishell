void	execute(void)
{
	t_pipes p;

    // if there's only one command and it's a builtin, execute it directly
	if (g_data.cur.cmd_count == 1 && is_builtin(g_data.cur.cmd_list[0]->cmd) == 1)
		execute_builtin();
	else
	{
        // otherwise, fork a new process
		g_data.sig.exec_pid = fork();
        
        // the child process will handle the command(s)
		if (g_data.sig.exec_pid == 0)
		{
            // setup the initial pipe structures
			init(&p);
            
            // pipefd is an array to hold the file descriptors for the pip
            
            // initially, we'll be reading from standard input
			int in_fd = STDIN;

            // loop over each command
			for (p.idx = 0; p.idx < g_data.cur.cmd_count; p.idx++)
			{
				// if this isn't the last command, we'll need a pipe for the next command
				if (p.idx < g_data.cur.cmd_count - 1)
				{
					pipe(pipefd);
				}

                // fork another process for the actual execution
				g_data.sig.child_pid = fork();
                
                // the child process will handle the execution
				if (g_data.sig.child_pid == 0)
				{
					if (in_fd != STDIN)
					{
                        // replace the standard input with the input pipe
						dup2(in_fd, STDIN);
                        
                        // we don't need the original file descriptor anymore
						close(in_fd);
					}

                    // if this isn't the last command, we'll need to setup the output pipe
					if (p.idx < g_data.cur.cmd_count - 1)
					{
                        // we don't need the read end of the pipe, so close it
						close(pipefd[READ_END]);
                        
                        // replace the standard output with the output pipe
						if (pipefd[WRITE_END] != STDOUT)
						{
							dup2(pipefd[WRITE_END], STDOUT);
							close(pipefd[WRITE_END]);
						}
					}

                    // execute the command
					execute_cmd(&p, p.idx);
				}
				else
				{
                    // the parent process doesn't need these file descriptors
					if (in_fd != STDIN)
					{
						close(in_fd);
					}
					if (p.idx < g_data.cur.cmd_count - 1)
					{
                        // close the write end of the pipe
						close(pipefd[WRITE_END]);
                        
                        // the next command will read from this pipe
						in_fd = pipefd[READ_END];
					}
				}
			}

            // wait for all child processes to finish
			while (waitpid(-1, NULL, 0) > 0);

            // exit the child process
			exit(0);
		}
		else
		{
			// the parent process waits for the main child process to finish
			waitpid(g_data.sig.exec_pid, NULL, 0);
			g_data.sig.exec_pid = -1;
		}
	}
}
