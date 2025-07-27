/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:27:38 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 13:15:58 by vzurera-         ###   ########.fr       */
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
		bool		running;
	}	t_malcolm;

#pragma endregion

#pragma region "Variables"

	extern t_malcolm g_malcolm;

#pragma endregion

#pragma region "Methods"

	int	parse_arguments(int argc, char **argv);

#pragma endregion
