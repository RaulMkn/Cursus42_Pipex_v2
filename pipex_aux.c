/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:11:42 by rmakende          #+#    #+#             */
/*   Updated: 2025/06/13 17:13:41 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	usage_exit(void)
{
	ft_printf("Usage:\n");
	ft_printf("./pipex file1 cmd1 cmd2 file2\n");
	ft_printf("./pipex here_doc LIMITER cmd1 cmd2 file\n");
	exit(EXIT_FAILURE);
}

void	handle_heredoc(int argc, char **argv, int *out_fd)
{
	char			*line;
	const char		*limiter = argv[2];
	const size_t	len = ft_strlen(limiter);

	if (strcmp(argv[1], "here_doc") != 0)
		return ;
	*out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd == -1)
		perror_exit("Error opening output file");
	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (strcmp(line, limiter) == 0 || (strlen(line) == len + 1
				&& line[len] == '\n' && strncmp(line, limiter, len) == 0))
		{
			free(line);
			break ;
		}
		write(*out_fd, line, strlen(line));
		free(line);
	}
	close(*out_fd);
}
