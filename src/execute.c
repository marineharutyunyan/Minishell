#include "mini.h"

int change_ia_for_execve(int mode, int	in, int out)
{
	return (1);
}

int execute(t_general *g_data)
{
	pid_t id;
	int     status;
	int     i = 0;
	int		fd[2];// fd[0] for read , fd[1] for write
	// printf("fsdg\n");
	// g_data->pipes[0].argv[0] = "dsgdsg";
	//  g_data->pipes[0].argv[1] = "-l";
	pipe(fd);
	printf("%d\n", fd[0]);
	printf("%d\n", fd[1]);
	// while (i < g_data->pipe_count)
	// {  
	// 	id = fork(); // TODO check ret_value;
	// 	if(id == 0)
	// 	{
	// 		if (i == 0 && change_ia_for_execve(0), )
	// 			execve("/bin/cat", g_data->pipes[i].argv, g_data->env);
	// 		else if (i == 1 && change_ia_for_execve(1))
	// 			execve("/bin/cat", g_data->pipes[i].argv, g_data->env);
	// 		else if (change_ia_for_execve(2))
	// 			execve("/bin/cat", g_data->pipes[i].argv, g_data->env);
	// 		exit(5);
	// 	} 
	// 	i++;
	// }
	// waitpid(id, &status, 0);
//     printf("status = %d\n", status);
//     printf("id of parent %d\n", id);
	
//     // if (WIFEXITED(status))  // TODO exit_status
//     // printf("%d\n", WEXITSTATUS(status)); //need to store the cheild exit status for
	return(0);
}