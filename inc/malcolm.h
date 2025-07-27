/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:27:38 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 19:28:35 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include "utils.h"
	#include "network.h"

	#include <unistd.h>			// close, sleep, getuid
	#include <signal.h>			// signal
	#include <stdio.h>			// printf
	#include <string.h>			// strerror

#pragma endregion

#pragma region "Structures"

	typedef struct s_malcolm {
		bool				running;
		char				if_name[16];
		char				source_ip[16];
		char				target_ip[16];
		struct sockaddr_in	source_addr;
		struct sockaddr_in	target_addr;
	}	t_malcolm;

#pragma endregion

#pragma region "Variables"

	extern t_malcolm g_malcolm;

#pragma endregion

#pragma region "Methods"

	int	parse_arguments(int argc, char **argv);

#pragma endregion
