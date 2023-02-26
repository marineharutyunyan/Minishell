#include "mini.h"

// int change_ia_for_execve(int mode, int	in, int out) //mode tells if the pipes fd is the fist one or the last one or in the midle 
// {
// 	return (1);
// }
//  cat main.c | cat | cat
int execute(t_general *g_data)
{
	pid_t id;
	int     status;
	int     i = 0;
	int		*fd[2]; // TODO create pipecount fd with in and out using malloc
	int		pipe1_fd[2];// fd[0] for read , fd[1] for write
	int		pipe2_fd[2];// fd[0] for read , fd[1] for write
	// printf("fsdg\n");
	// g_data->pipes[0].argv[0] = "dsgdsg";
	//  g_data->pipes[0].argv[1] = "-l";
	pipe(pipe1_fd);
	pipe(pipe2_fd);
	// printf("pipe1_fd = %d\n", pipe1_fd[0]);
	// printf("pipe1_fd = %d\n", pipe1_fd[1]);
	// printf("pipe2_fd = %d\n", pipe2_fd[0]);
	// printf("pipe2_fd = %d\n", pipe2_fd[1]);
	while (i < g_data->pipe_count)
	{  
		id = fork(); // TODO check ret_value;
		if(id == 0)
		{
			if (i == 0/* && change_ia_for_execve(0), */)
			{
				dup2(pipe1_fd[1], 1); 	
				close(pipe1_fd[0]);
	close(pipe1_fd[1]);
	close(pipe2_fd[0]);
	close(pipe2_fd[1]);
				close(pipe1_fd[1]);
				execve("/bin/cat", g_data->pipes[i].argv, g_data->env);
			}
			else if (i == 1/* && change_ia_for_execve(1)*/)
			{
				dup2(pipe1_fd[0], 0);
				dup2(pipe2_fd[1], 1);
				close(pipe1_fd[0]);
	close(pipe1_fd[1]);
	close(pipe2_fd[0]);
	close(pipe2_fd[1]);
				execve("/bin/cat", g_data->pipes[i].argv, g_data->env);
			}
			else /*if (change_ia_for_execve(2))*/
			{
				dup2(pipe2_fd[0], 0);
	close(pipe1_fd[0]);
	close(pipe1_fd[1]);
	close(pipe2_fd[0]);
	close(pipe2_fd[1]);
				execve("/bin/cat", g_data->pipes[i].argv, g_data->env);
			}
			exit(5);
		} 
		i++;
	}
	close(pipe1_fd[0]);
	close(pipe1_fd[1]);
	close(pipe2_fd[0]);
	close(pipe2_fd[1]);
	waitpid(id, &status, 0);
//     printf("status = %d\n", status);
//     printf("id of parent %d\n", id);
//     // if (WIFEXITED(status))  // TODO exit_status
//     // printf("%d\n", WEXITSTATUS(status)); //need to store the cheild exit status for
	return(0);
}