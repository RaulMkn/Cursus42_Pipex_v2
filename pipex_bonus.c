/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:26:56 by rmakende          #+#    #+#             */
/*   Updated: 2025/07/07 20:12:13 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	if_forker(int fd[2], char *argv[], char **envp, int *i)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute_command(argv[*i], envp);
}

void	else_forker(int fd[2], pid_t pid)
{
	int	status;

	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	waitpid(pid, &status, 0);
}

int	main_handler(int argc, char **argv, int *out_fd, int *flag_error)
{
	int	in_fd;
	int	i;

	i = 3;
	if (argc < 5)
		exit(1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		handle_heredoc(argc, argv, out_fd);
	else
	{
		in_fd = open(argv[1], O_RDONLY);
		if (in_fd == -1)
			in_fd = open("/dev/null", O_RDONLY);
		*out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*out_fd == -1)
		{
			perror("pipex: error");
			*flag_error = 1;
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		i = 2;
	}
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		out_fd;
	int		i;
	int		flag_error;

	i = main_handler(argc, argv, &out_fd, &flag_error);
	while (i < argc - 2)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			if_forker(fd, argv, envp, &i);
		else
			else_forker(fd, pid);
		i++;
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (flag_error == 1)
		exit(1);
	execute_command(argv[argc - 2], envp);
	while (wait(NULL) > 0)
		;
	return (1);
}
