/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:46:47 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 13:53:24 by vzurera-         ###   ########.fr       */
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
		// freeifaddrs(ifaddr);
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

		int result = set_signals();
		if (!result) result = parse_arguments(argc, argv);
		if (!result) result = create_socket();
		if (!result) result = get_interface();
		if (!result) result = receive_request();
		if (!result) result = send_reply();

		if (result != 1) fprintf(stdout, "\rExiting program...\n");

		return (result != 1);
	}

#pragma endregion
