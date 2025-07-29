/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:46:47 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/29 14:53:49 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"

	#include <unistd.h>
	#include <signal.h>

#pragma endregion

#pragma region "Variables"

	t_malcolm g_malcolm;

#pragma endregion

#pragma region "Signals"

	static void termination_handler(int sig) {
		(void) sig;
		g_malcolm.running = 0;

		if (g_malcolm.sockfd != -1) close(g_malcolm.sockfd);
		g_malcolm.sockfd = -1;
	}

	static int set_signals() {
		signal(SIGINT,  termination_handler);
		signal(SIGQUIT, termination_handler);
		signal(SIGTERM, termination_handler);
		signal(SIGHUP,  termination_handler);

		return (0);
	}

#pragma endregion

#pragma region "Main"

	int main(int argc, char **argv) {
		ft_memset(&g_malcolm, 0, sizeof(t_malcolm));
		g_malcolm.sockfd = -1;
		g_malcolm.running = 1;

		int result = set_signals();
		if (!result && g_malcolm.running) result = parse_arguments(argc, argv);
		if (!result && g_malcolm.running) result = get_interface();
		if (!result && g_malcolm.running) result = create_socket();
		if (!result && g_malcolm.running) result = receive_request();
		if (!result && g_malcolm.running) result = send_reply();

		if (result != 1) fprintf(stdout, "\rExiting program...\n");

		return (result != 1);
	}

#pragma endregion
